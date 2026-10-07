#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace rental
{

    class MaintenanceRecord
    {
    private:
        static constexpr auto TAG = "maintenance_record";
        static constexpr auto BASE_DESC = "Regular Maintenance";

    protected:
        std::uint64_t m_id{ 0 };
        std::string m_workDescription{ BASE_DESC };
        double m_cost{ 0.0 };
        std::int64_t m_dateTimestamp{ 0 };

    public:
        // Конструктор (функция создания объекта)
        MaintenanceRecord(std::uint64_t id, std::string_view description, double cost, std::int64_t timestamp);

        // Запрещаем создание "пустого" объекта и его копирование
        MaintenanceRecord() = delete;
        MaintenanceRecord(const MaintenanceRecord&) = delete;
        MaintenanceRecord& operator=(const MaintenanceRecord&) = delete;

        // Разрешаем перемещение в памяти
        MaintenanceRecord(MaintenanceRecord&&) = default;
        MaintenanceRecord& operator=(MaintenanceRecord&&) = default;

        // Деструктор (функция уничтожения объекта)
        ~MaintenanceRecord();

        // Геттеры (получение значений)
        [[nodiscard]] std::uint64_t GetId() const
        {
            return m_id;
        }

        [[nodiscard]] std::string_view GetDescription() const
        {
            return m_workDescription;
        }

        [[nodiscard]] double GetCost() const
        {
            return m_cost;
        }

        [[nodiscard]] std::int64_t GetDate() const
        {
            return m_dateTimestamp;
        }

        // Сеттеры (изменение значений)
        void SetDescription(std::string_view description)
        {
            m_workDescription = std::string(description);
        }

        void SetCost(double cost)
        {
            m_cost = cost;
        }
    };

} // namespace rental