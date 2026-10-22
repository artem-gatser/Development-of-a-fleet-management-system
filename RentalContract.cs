using System;

namespace FleetManagement
{
    public enum ContractState
    {
        Active,
        Completed
    }

    public class RentalContract
    {
        private const string Tag = "rental_contract";

        public ulong ContractId { get; }
        public string ClientName { get; }
        public uint DriverExperienceYears { get; }
        public uint RentalDays { get; }
        public double DailyRate { get; }
        public double TotalCost => RentalDays * DailyRate;
        public ContractState State { get; private set; } = ContractState.Active;

        // Агрегация: ссылка на внешний объект Vehicle
        private readonly Vehicle _targetVehicle;

        public RentalContract(ulong id, string clientName, uint driverExperience, Vehicle vehicle, uint days, double dailyRate)
        {
            ContractId = id;
            ClientName = clientName;
            DriverExperienceYears = driverExperience;
            // Если параметр vehicle оказался null, аварийно прерываем работу и выдаем ошибку
            _targetVehicle = vehicle ?? throw new ArgumentNullException(nameof(vehicle));
            RentalDays = days;
            DailyRate = dailyRate;

            Console.WriteLine($"[{Tag}] Created contract id: {ContractId} for client: {ClientName}");
        }

        public bool ProcessIssue()
        {
            if (DriverExperienceYears < 3)
            {
                Console.WriteLine($"[{Tag}] Rental denied for contract id: {ContractId} (driver experience is {DriverExperienceYears} years, minimum required is 3 years)");
                return false;
            }

            if (!_targetVehicle.CanBeRented())
            {
                Console.WriteLine($"[{Tag}] Rental denied: Vehicle cannot be rented due to low battery.");
                return false;
            }

            State = ContractState.Active;
            Console.WriteLine($"[{Tag}] Contract id: {ContractId} successfully issued and active!");
            return true;
        }

        public void CompleteContract()
        {
            State = ContractState.Completed;
            Console.WriteLine($"[{Tag}] Contract id: {ContractId} is now completed.");
        }
    }
}