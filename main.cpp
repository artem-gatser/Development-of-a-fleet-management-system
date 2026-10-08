#include "vehicle.hpp"
#include "rental_contract.hpp"
#include <iostream>

int main()
{

    std::cout << "STARTING VEHICLE RENTAL SYSTEM TESTS\n\n";

    // Создаем автомобиль с нормальным зарядом и пробегом
    rental::Vehicle myCar(101, "Tesla Model 3", 85.0, 15000.0);
    myCar.AddMaintenanceRecord(1, "Battery check and tire replacement", 250.0, 1728000000);

    std::cout << "\nTEST 1: Rental attempt by a client with less than 3 years experience (should fail)\n";
    {
        // Передача объекта по указателю (&myCar)
        rental::RentalContract badContract(501, "Ivan", 1, &myCar, 3, 50.0);
        badContract.ProcessIssue();
    } // Договор уничтожится, а машина останется цела (агрегация).

    std::cout << "\nTEST 2: Successful rental by a client with sufficient experience (>= 3 years)\n";
    {
        rental::RentalContract goodContract(502, "Alex", 5, &myCar, 5, 50.0);
        if (goodContract.ProcessIssue())
        {
            std::cout << "Contract is active! Vehicle issued to the client.\n";
            goodContract.CompleteContract();
        }
    }

    std::cout << "\nTEST 3: Object Lifespan Check (Composition demonstration)\n";
    {
        std::cout << "Creating a temporary vehicle inside a local scope...\n";
        rental::Vehicle tempCar(102, "Nissan Leaf", 90.0, 5000.0);
        tempCar.AddMaintenanceRecord(2, "Software update", 50.0, 1728000100);
        std::cout << "Leaving the scope. The vehicle will now be destroyed along with its maintenance history...\n";
    } // tempCar уничтожится вместе с вектором истории ТО (композиция).

    std::cout << "\nTEST 4: Dynamic memory allocation (new / delete) & Pointers\n";
    {
        // Динамическое создание объекта класса через оператор new
        rental::Vehicle* dynCar = new rental::Vehicle(103, "Audi e-tron", 75.0, 12000.0);
        dynCar->AddMaintenanceRecord(3, "Inspection", 100.0, 1728000200);

        std::cout << "Dynamic vehicle created with ID: " << dynCar->GetId() << "\n";

        // Явное удаление динамического объекта через delete (вызовет деструктор Vehicle)
        delete dynCar;
        std::cout << "Dynamic vehicle successfully deleted via delete operator.\n";
    }

    std::cout << "\nTEST 5: Array of dynamic objects (Array of pointers)\n";
    {
        const int fleetSize = 2;
        // Массив динамических объектов (массив указателей на Vehicle)
        rental::Vehicle* dynamicFleet[fleetSize];

        dynamicFleet[0] = new rental::Vehicle(104, "Hyundai Ioniq", 88.0, 8000.0);
        dynamicFleet[1] = new rental::Vehicle(105, "VW ID.4", 92.0, 4000.0);

        for (int i = 0; i < fleetSize; ++i)
        {
            std::cout << "Fleet vehicle " << i + 1 << " model: " << dynamicFleet[i]->GetModel() << "\n";
        }

        // Обязательное освобождение памяти каждого элемента массива
        for (int i = 0; i < fleetSize; ++i)
        {
            delete dynamicFleet[i];
        }
    }

    std::cout << "\n=== TESTING COMPLETED, EXITING MAIN ===\n";
    return 0;
}