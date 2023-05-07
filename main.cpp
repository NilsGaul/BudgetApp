#include "budget_app.h"

int main(){
    std::cout << "Starting application" << std::endl;

    budget_app::Category food("food");
    budget_app::Category clothing("clothing");
    budget_app::Category entertainment("entertainment");
    std::vector<budget_app::Category*> allCategories;
    allCategories.push_back(&food);
    allCategories.push_back(&clothing);
    allCategories.push_back(&entertainment);

    food.deposit(200, "My monthly budget");
    clothing.deposit(150, "My monthly budget");
    entertainment.deposit(50, "My monthly budget");
    food.deposit(100, "Extra budget for dinner party with friends");
    food.withdraw(20, "get some groceries");
    clothing.withdraw(10, "new shirt");
    entertainment.withdraw(25, "theatre evening");
    clothing.transfer(15, &entertainment, "rather spend it on fun then new clothes");

    std::cout << "Food balance: " << food.getBalance() << ".\n";
    std::cout << "Clothing balance: " << clothing.getBalance() << ".\n"; 
    std::cout << "Entertainment balance: " << entertainment.getBalance() << ".\n"; 
    food.showLedger();
    clothing.showLedger();
    entertainment.showLedger();
    budget_app::balance_across_categories(allCategories);

    std::cout << "Finish application" << std::endl;
}