#ifndef BUDGET_APP_H_
#define BUDGET_APP_H_

#include <list>
#include <vector>
#include <iostream>

namespace budget_app {

struct LedgerEntry
{
    std::string entry_type;
    std::string entry_description;
    int entry_amount;
    int entry_balance;

    LedgerEntry(std::string operation_type, std::string description, int amount, int balance)
    {
        entry_type = operation_type;
        entry_description = description;
        entry_amount = amount;
        entry_balance = balance;
    }
};

class Category 
{
    private:
        std::string name_;
        int balance_;
        std::list<LedgerEntry> ledger_;

    public:
    Category(std::string name)
    {
        name_ = name;
        balance_ = 0;
        LedgerEntry entry = LedgerEntry("Open new ledger", "Init Ledger", 0, 0);
        ledger_ = {entry};
        std::cout << "New budget category " + name_ + " was opened.\n";
    }

    void deposit(int amount, std::string description="")
    {
        balance_ += amount;
        LedgerEntry entry = LedgerEntry("Deposit", description, amount, balance_);
        ledger_.push_back(entry);
        std::cout << "New deposit of " << amount << " from category '" + name_ + "' with description '" + description + "'.\n";
    }

    void withdraw(int amount, std::string description="")
    {
        balance_ -= amount;
        LedgerEntry entry = LedgerEntry("Withdraw", description, amount, balance_);
        ledger_.push_back(entry);
        std::cout << "New withdraw of " << amount << " from '" + name_ + "' with description '" + description + "'.\n";
    }

    std::string getName()
    {
        return name_;
    }

    int getBalance()
    {
        return balance_;
    }

    void showLedger()
    {
        std::cout << "These are all ledger entries of category '" + name_ + "'.\n";
        for(auto it = ledger_.begin(); it != ledger_.end(); ++it)
        {
            std::cout << "Type: " + it->entry_type + ", description: '" + it->entry_description 
                + "', amount: " << it->entry_amount <<  ", balance: " << it->entry_balance << ".\n";
        }
    }

    void transfer(int amount, Category *target_category, std::string description="")
    {
        std::cout << "Transfer '" << amount << "' from category '" + name_ + "' to target category '" + target_category->name_ + "'.\n";
        withdraw(amount, "Transfer: " + description);
        target_category->deposit(amount, "Transfer: " + description);        
    }
};

void balance_across_categories(std::vector<Category*> &categories)
{
    std::cout << "Currently there are '" << categories.size() << "' categories.\n";
    int total_balance = 0;
    for(std::vector<Category*>::iterator it = categories.begin(); it != categories.end(); ++it)
    {
        total_balance += (*it)->getBalance();
    }
    std::cout << "The total balance across all categories is '" << total_balance << "'.\n";
    for(std::vector<Category*>::iterator it = categories.begin(); it != categories.end(); ++it)
    {
        double share = (double)(*it)->getBalance()/(double)total_balance;
        std::cout << "Category '" + (*it)->getName() + "' has a share of " << share << " of the total balance.\n";
    }
}

} //namespace budget_app

#endif //BUDGET_APP_H_