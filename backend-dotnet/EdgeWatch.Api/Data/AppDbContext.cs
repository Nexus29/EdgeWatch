using Microsoft.EntityFrameworkCore;
using EdgeWatch.Api.Models;

public class AppDbContext : DbContext
{
    public DbSet<DeviceData> DeviceData { get; set; }
    public DbSet<Alert> Alerts { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder options)
        => options.UseMySql(
            "server=localhost;database=edgewatch;user=root;password=root",
            ServerVersion.AutoDetect("server=localhost;database=edgewatch;user=root;password=root")
        );
}
