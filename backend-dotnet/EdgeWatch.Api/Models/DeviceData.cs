namespace EdgeWatch.Api.Models;

public class DeviceData
{
	public int Id { get; set; }
	public int DeviceId { get; set; }
	public float Cpu { get; set; }
	public float Temperature { get; set; }
	public DateTime CreatedAt { get; set; } = DateTime.Now;
}
