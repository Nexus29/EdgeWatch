public class Alert {
    public int Id { get; set; }
    public int DeviceId { get; set; }
    public string Message { get; set; }
    public DateTime CreatedAt { get; set; } = DateTime.Now;
}
