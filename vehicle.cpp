#include "vehicle.hpp"
#include <iostream>

namespace rental
{

    // Конструктор автомобиля
    Vehicle::Vehicle(std::uint64_t id, std::string_view model, double batteryLevel, double mileage)
        : m_id{ id }
        , m_model{ model }
        , m_batteryLevel{ batteryLevel }
        , m_mileage{ mileage }
    {
        std::cout << "[" << TAG << "] Created vehicle id: " << m_id
            << ", model: " << m_model << "\n";
    }

    // Деструктор автомобиля
    Vehicle::~Vehicle()
    {
        std::cout << "[" << TAG << "] Destroyed vehicle id: " << m_id
            << ". Its maintenance history will be automatically deleted.\n";
        // Вектор m_maintenanceHistory автоматически очищается, вызывая деструкторы всех записей о ТО, которые в нем хранились.
    }

    // Метод добавления записи о техобслуживании
    void Vehicle::AddMaintenanceRecord(std::uint64_t id, std::string_view description, double cost, std::int64_t timestamp)
    {
        // emplace_back прямо внутри вектора создает объект MaintenanceRecord
        m_maintenanceHistory.emplace_back(id, description, cost, timestamp);
        std::cout << "[" << TAG << "] Added maintenance record to vehicle id: " << m_id << "\n";
    }

    // Проверка правила: можно ли выдать авто (заряд >= 20%)
    bool Vehicle::CanBeRented() const
    {
        if (m_batteryLevel < 20.0)
        {
            std::cout << "[" << TAG << "] Cannot rent vehicle id: " << m_id
                << " (battery level is too low: " << m_batteryLevel << "%)\n";
            return false;
        }
        return true;
    }

} // namespace rental