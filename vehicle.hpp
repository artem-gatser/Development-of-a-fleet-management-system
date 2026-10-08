#pragma once

#include "maintenance_record.hpp"
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace rental
{

    class Vehicle
    {
    private:
        static constexpr auto TAG = "vehicle";

    protected:
        std::uint64_t m_id{ 0 };
        std::string m_model{};
        double m_batteryLevel{ 100.0 }; // Уровень заряда или топлива в процентах
        double m_mileage{ 0.0 };        // Пробег автомобиля

        // Композиция: в векторе хранятся записи о ТО, принадлежащие конкретно этой машине
        std::vector<MaintenanceRecord> m_maintenanceHistory;

    public:
        Vehicle(std::uint64_t id, std::string_view model, double batteryLevel, double mileage);

        Vehicle() = delete;
        Vehicle(const Vehicle&) = delete;
        Vehicle& operator=(const Vehicle&) = delete;

        Vehicle(Vehicle&&) = default;
        Vehicle& operator=(Vehicle&&) = default;

        ~Vehicle();

        [[nodiscard]] std::uint64_t GetId() const
        {
            return m_id;
        }

        [[nodiscard]] std::string_view GetModel() const
        {
            return m_model;
        }

        [[nodiscard]] double GetBatteryLevel() const
        {
            return m_batteryLevel;
        }

        [[nodiscard]] double GetMileage() const
        {
            return m_mileage;
        }

        // Метод добавления записи о техобслуживании (реализация композиции)
        void AddMaintenanceRecord(std::uint64_t id, std::string_view description, double cost, std::int64_t timestamp);

        // Метод проверки: можно ли арендовать машину (заряд >= 20%)
        [[nodiscard]] bool CanBeRented() const;
    };

} // namespace rental