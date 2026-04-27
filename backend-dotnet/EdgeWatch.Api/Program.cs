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

	return Results.Ok();
});

app.MapPost("/alerts", async (Alert alert) =>
{
	using var db = new AppDbContext();
	db.Alerts.Add(alert);
	await db.SaveChangesAsync();

	return Results.Ok();
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

app.MapGet("/devices/{id}", async (int id) =>
{
	using var db = new AppDbContext();

	var data = db.DeviceData
		.Where(d => d.DeviceId == id)
		.OrderByDescending(d => d.CreatedAt)
		.Take(1)
		.ToList();

	return Results.Ok(data);
});

app.Run();
