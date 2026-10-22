using System;
using System.Collections.Generic;

namespace FleetManagement
{
    public class Vehicle
    {
        public ulong Id { get; }
        public string Model { get; }
        private double _batteryLevel;

        public double BatteryLevel
        {
            get
            {
                return _batteryLevel;
            }
            private set
            {
                _batteryLevel = Math.Max(0.0, Math.Min(100.0, value));
            }
        }

        public double Mileage { get; private set; }

        // Композиция: коллекция создается внутри конструктора Vehicle
        private readonly List<MaintenanceRecord> _maintenanceHistory;

        public Vehicle(ulong id, string model, double batteryLevel, double mileage)
        {
            Id = id;
            Model = model;
            BatteryLevel = batteryLevel;
            Mileage = mileage;
            _maintenanceHistory = new List<MaintenanceRecord>();
            Console.WriteLine($"[vehicle] Created vehicle id: {Id}, model: {Model}");
        }

        public void AddMaintenanceRecord(ulong id, string description, double cost, long timestamp)
        {
            _maintenanceHistory.Add(new MaintenanceRecord(id, description, cost, timestamp));
            Console.WriteLine($"[vehicle] Added maintenance record to vehicle id: {Id}");
        }

        public bool CanBeRented() => BatteryLevel >= 20.0;

        public override string ToString() => $"{Model} (ID: {Id}, Заряд: {BatteryLevel}%, Пробег: {Mileage} км)";
    }
}