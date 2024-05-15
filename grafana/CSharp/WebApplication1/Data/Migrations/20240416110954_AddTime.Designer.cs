﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using WebApplication1.Data;

#nullable disable

namespace WebApplication1.Data.Migrations
{
    [DbContext(typeof(ApplicationDbContext))]
    [Migration("20240416110954_AddTime")]
    partial class AddTime
    {
        /// <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "8.0.0")
                .HasAnnotation("Relational:MaxIdentifierLength", 64);

            modelBuilder.Entity("WebApplication1.Data.Models.DataEntry", b =>
                {
                    b.Property<Guid>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("char(36)");

                    b.Property<float>("AccelerationX")
                        .HasColumnType("float");

                    b.Property<float>("AccelerationY")
                        .HasColumnType("float");

                    b.Property<float>("AccelerationZ")
                        .HasColumnType("float");

                    b.Property<float>("GyroX")
                        .HasColumnType("float");

                    b.Property<float>("GyroY")
                        .HasColumnType("float");

                    b.Property<float>("GyroZ")
                        .HasColumnType("float");

                    b.Property<int>("TimeStampInt")
                        .HasColumnType("int");

                    b.Property<TimeOnly>("Timestamp")
                        .HasColumnType("time(6)");

                    b.Property<DateTime>("time")
                        .HasColumnType("datetime(6)");

                    b.HasKey("Id");

                    b.ToTable("DataEntries");
                });
#pragma warning restore 612, 618
        }
    }
}
