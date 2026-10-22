using System;

namespace FleetManagement
{
    public class MaintenanceRecord
    {
        public ulong Id { get; }
        public string Description { get; set; }
        public double Cost { get; set; }
        public long Timestamp { get; }

        public MaintenanceRecord(ulong id, string description, double cost, long timestamp)
        {
            Id = id;
            Description = description;
            Cost = cost;
            Timestamp = timestamp;
            Console.WriteLine($"[maintenance_record] Created maintenance record id: {Id}, cost: {Cost}");
        }

        public override string ToString()
        {
            return $"Запись ТО #{Id}: {Description}, Стоимость: {Cost}";
        }
    }
}