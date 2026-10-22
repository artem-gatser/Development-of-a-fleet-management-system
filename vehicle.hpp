#pragma once
#include "maintenance_record.hpp"
#include <cstdint>
#include <string>
#include <string_view>
#include <memory>

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

        // Замена массива MaintenanceRecord** на массив умных указателей (композиция)
        std::unique_ptr<MaintenanceRecord> m_maintenanceHistory[10];
        std::size_t m_maintenanceCount{ 0 };              // Текущее количество записей

    public:
        Vehicle(std::uint64_t id, std::string_view model, double batteryLevel, double mileage);

        // Запрет на создание объектов без параметров
        Vehicle() = delete;

        // Запрет копирования
        Vehicle(const Vehicle&) = delete;
        Vehicle& operator=(const Vehicle&) = delete;

        // Операции перемещения генерируются компилятором автоматически (благодаря unique_ptr)
        Vehicle(Vehicle&&) noexcept = default;
        Vehicle& operator=(Vehicle&&) noexcept = default;

        // Деструктор больше не нужен, unique_ptr очистят память автоматически
        ~Vehicle() = default;

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