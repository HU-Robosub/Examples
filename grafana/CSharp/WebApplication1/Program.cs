using Microsoft.EntityFrameworkCore;
using WebApplication1;
using WebApplication1.Data;
using WebApplication1.Data.Models;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var connectionString = builder.Configuration.GetConnectionString("DefaultConnection");

Console.WriteLine(connectionString);
builder.Services.AddDbContextFactory<ApplicationDbContext>((_, options) =>
{
    options.UseMySql(connectionString,
        ServerVersion.AutoDetect(connectionString),
        optionsBuilder =>
        {
            optionsBuilder.EnableRetryOnFailure();
        });
});

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

await using var serviceScope = app.Services.CreateAsyncScope();
var context = serviceScope.ServiceProvider.GetRequiredService<ApplicationDbContext>();

if (context.Database.GetPendingMigrations().Any())
{
    context.Database.Migrate();
}

const string directoryToWatch = @"/app/logs";
const string fileFilter = "*.log";

var watcher = new FileAppenderWatcher(directoryToWatch, fileFilter);
watcher.FileAppended += OnFileAppended;

async void OnFileAppended(object sender, FileAppendedEventArgs e)
{
    if (e.ChangeType == WatcherChangeTypes.Changed)
    {
        var stream = await File.ReadAllLinesAsync(e.FilePath);
        var last = stream.Last();

        await using var scope = app.Services.CreateAsyncScope();
        var context = scope.ServiceProvider.GetRequiredService<ApplicationDbContext>();

        try
        {
            var timeStampInt = int.Parse(last.Split(',')[0]);
            if (await context.DataEntries.AnyAsync(x => x.TimeStampInt == timeStampInt))
            {
                Console.WriteLine("Skipping");
                return;
            }
            
            await context.DataEntries.AddAsync(new DataEntry()
            {
                Id = Guid.NewGuid(),
                Timestamp = TimeOnly.FromDateTime(DateTime.Now),
                time = DateTime.Now,
                TimeStampInt = timeStampInt,
                AccelerationX = float.Parse(last.Split(',')[4]),
                AccelerationY = float.Parse(last.Split(',')[5]),
                AccelerationZ = float.Parse(last.Split(',')[6]),
                GyroX = float.Parse(last.Split(',')[1]),
                GyroY = float.Parse(last.Split(',')[2]),
                GyroZ = float.Parse(last.Split(',')[3])
            });

            await context.SaveChangesAsync();
        }
        catch
        {
            // ignore
        }
    }
    Console.WriteLine($"File appended: {e.FilePath}, Change type: {e.ChangeType}");
}
watcher.EnableRaisingEvents = true;

Console.WriteLine("Press Enter to exit.");
Console.ReadLine();

app.Run();