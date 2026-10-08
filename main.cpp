#include "vehicle.hpp"
#include "rental_contract.hpp"
#include <iostream>

int main()
{

    std::cout << "STARTING VEHICLE RENTAL SYSTEM TESTS\n\n";

    // 1. Создаем автомобиль с нормальным зарядом и пробегом
    // (Машина создается на стеке в функции main)
    rental::Vehicle myCar(101, "Tesla Model 3", 85.0, 15000.0);

    // Добавляем запись о ТО (Демонстрация КОМПОЗИЦИИ)
    myCar.AddMaintenanceRecord(1, "Battery check and tire replacement", 250.0, 1728000000);

    std::cout << "\nRental attempt by a client with less than 3 years experience (should fail)\n";
    {
        // Создаем договор аренды внутри блока
        // Клиент Иван, стаж всего 1 год (< 3 лет)
        rental::RentalContract badContract(501, "Ivan", 1, &myCar, 3, 50.0);

        // Пытаемся оформить договор
        badContract.ProcessIssue();

    } // Здесь договор выходит из области видимости и уничтожится.
      // Сам договор удалится, но машина (myCar) останется цела.

    std::cout << "\nSuccessful rental by a client with sufficient experience (>= 3 years)\n";
    {
        // Клиент Алексей, стаж 5 лет
        rental::RentalContract goodContract(502, "Alex", 5, &myCar, 5, 50.0);

        // Оформляем договор
        if (goodContract.ProcessIssue())
        {
            std::cout << "Contract is active! Vehicle issued to the client.\n"; // исправлено на английский текст
            goodContract.CompleteContract();
        }
    } // Договор удаляется, машина продолжает существовать.

    std::cout << "\nObject Lifespan Check (Composition)\n";
    {
        std::cout << "Creating a temporary vehicle inside a local scope...\n";
        rental::Vehicle tempCar(102, "Nissan Leaf", 90.0, 5000.0);
        tempCar.AddMaintenanceRecord(2, "Software update", 50.0, 1728000100);

        std::cout << "Leaving the scope. The vehicle will now be destroyed along with its maintenance history...\n";
    } // Уничтожится tempCar, и деструктор вектором автоматически уберет запись о техобслуживании "Software update".

    std::cout << "\nTESTING COMPLETED, EXITING MAIN\n";
    return 0;
}