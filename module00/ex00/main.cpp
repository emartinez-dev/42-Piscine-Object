/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:53:59 by franmart          #+#    #+#             */
/*   Updated: 2024/10/25 21:41:13 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include "Bank.hpp"

int main() {
    Bank bank;

	// Create new accounts
	long acc1 = bank.create_account();
	long acc2 = bank.create_account();

	std::cout << "Created accounts with IDs: " << acc1 << " and " << acc2 << std::endl;

	// Deposit into accounts
	bank.deposit(acc1, 5000);
	bank.deposit(acc2, 3000);

	std::cout << "Balance after deposit - Account " << acc1 << ": " 
				<< bank.get_account(acc1).get_balance() << std::endl;
	std::cout << "Balance after deposit - Account " << acc2 << ": " 
				<< bank.get_account(acc2).get_balance() << std::endl;

	// Withdraw from accounts
	bank.withdraw(acc1, 1000);
	std::cout << "Balance after withdrawal - Account " << acc1 << ": " 
				<< bank.get_account(acc1).get_balance() << std::endl;

	// Take a loan
	bank.loan(acc2, 100);
	std::cout << "Balance after loan - Account " << acc2 << ": " 
				<< bank.get_account(acc2).get_balance() << ", Debt: " 
				<< bank.get_account(acc2).get_debt() << std::endl;

	// Modify account balance
	bank.modify_account(acc1, 8000);
	std::cout << "Balance after modifying - Account " << acc1 << ": " 
				<< bank.get_account(acc1).get_balance() << std::endl;

	// Bank liquidity check
	std::cout << "Bank Liquidity: " << bank.get_liquidity() << std::endl;

	// Remove an account
	if (bank.remove_account(acc2))
		std::cout << "Account " << acc2 << " removed successfully." << std::endl;

	// Try to access removed account to test exception
	try {
		bank.get_account(acc2);
	} catch (std::exception &e) {
		std::cerr << e.what();
	}

	// Add a few more accounts
	for (int i = 0; i < 20; i++)
	{
		long id = bank.create_account();
		bank.deposit(id, i * i);
	}

	// Print final bank status
	std::cout << bank;

    return (0);
}
