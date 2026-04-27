using EdgeWatch.Api.Models;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

// Auto-create database & tables
using (var scope = app.Services.CreateScope())
{
	using var db = new AppDbContext();
	db.Database.EnsureCreated();
}

// Store new data
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

// View all stored data
app.MapGet("/metrics", () =>
{
	using var db = new AppDbContext();
	return db.DeviceData.ToList();
});

app.MapGet("/alerts", () =>
{
	using var db = new AppDbContext();
	return db.Alerts.ToList();
});

app.Run();
