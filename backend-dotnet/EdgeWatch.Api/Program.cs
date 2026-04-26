using EdgeWatch.Api.Models;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapPost("/metrics", async (DeviceData data) =>
{
    using var db = new AppDbContext();
    db.DeviceData.Add(data);
    await db.SaveChangesAsync();
});

app.MapPost("/alerts", async (Alert alert) =>
{
    using var db = new AppDbContext();
    db.Alerts.Add(alert);
    await db.SaveChangesAsync();
});

app.Run();
