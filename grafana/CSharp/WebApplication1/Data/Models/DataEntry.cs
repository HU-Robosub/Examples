namespace WebApplication1.Data.Models;

public class DataEntry
{
    public Guid Id { get; set; }
    public TimeOnly Timestamp { get; set; }
    public DateTime time { get; set; }
    public int TimeStampInt { get; set; }
    public float AccelerationX { get; set; }
    public float AccelerationY { get; set; }
    public float AccelerationZ { get; set; }
    public float GyroX { get; set; }
    public float GyroY { get; set; }
    public float GyroZ { get; set; }
}