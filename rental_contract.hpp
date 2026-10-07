#pragma once

#include "vehicle.hpp"
#include <cstdint>
#include <string>
#include <string_view>

namespace rental
{

    enum class ContractState
    {
        eActive,
        eCompleted
    };

    class RentalContract
    {
    private:
        static constexpr auto TAG = "rental_contract";

    protected:
        std::uint64_t m_contractId{ 0 };
        std::string m_clientName{};
        std::uint32_t m_driverExperienceYears{ 0 }; // Стаж вождения в годах
        std::uint32_t m_rentalDays{ 0 };
        double m_dailyRate{ 0.0 };
        double m_totalCost{ 0.0 };
        ContractState m_state{ ContractState::eActive };

        // АГРЕГАЦИЯ: Указатель на сторонний объект Vehicle (автомобиль не принадлежит договору)
        Vehicle* m_targetVehicle{ nullptr };

    public:
        RentalContract(std::uint64_t id, std::string_view clientName, std::uint32_t driverExperience,
            Vehicle* vehicle, std::uint32_t days, double dailyRate);

        RentalContract() = delete;
        RentalContract(const RentalContract&) = delete;
        RentalContract& operator=(const RentalContract&) = delete;

        RentalContract(RentalContract&&) = default;
        RentalContract& operator=(RentalContract&&) = default;

        ~RentalContract();

        [[nodiscard]] std::uint64_t GetId() const
        {
            return m_contractId;
        }

        [[nodiscard]] ContractState GetState() const
        {
            return m_state;
        }

        [[nodiscard]] double GetTotalCost() const
        {
            return m_totalCost;
        }

        // Метод оформления договора с проверкой стажа и заряда машины
        bool ProcessIssue();

        // Завершение договора
        void CompleteContract();
    };

} // namespace rental