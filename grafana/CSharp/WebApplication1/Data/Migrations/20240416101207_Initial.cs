using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebApplication1.Data.Migrations
{
    /// <inheritdoc />
    public partial class Initial : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AlterDatabase()
                .Annotation("MySql:CharSet", "utf8mb4");

            migrationBuilder.CreateTable(
                name: "DataEntries",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "char(36)", nullable: false, collation: "ascii_general_ci"),
                    Timestamp = table.Column<TimeOnly>(type: "time(6)", nullable: false),
                    AccelerationX = table.Column<float>(type: "float", nullable: false),
                    AccelerationY = table.Column<float>(type: "float", nullable: false),
                    AccelerationZ = table.Column<float>(type: "float", nullable: false),
                    GyroX = table.Column<float>(type: "float", nullable: false),
                    GyroY = table.Column<float>(type: "float", nullable: false),
                    GyroZ = table.Column<float>(type: "float", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_DataEntries", x => x.Id);
                })
                .Annotation("MySql:CharSet", "utf8mb4");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "DataEntries");
        }
    }
}
