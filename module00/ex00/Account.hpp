/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:53:12 by franmart          #+#    #+#             */
/*   Updated: 2024/10/25 21:32:42 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

# include <iostream>

class Account
{
	private:
		long	_id;
		long	_balance;
		long	_debt;

	public:
		Account();
		Account(long id);
		~Account();
		Account(Account const &copy);
		Account	&operator=(Account const &copy);

		long	add_amount(long amount);
		long	withdraw_amount(long amount);

		long	loan_amount(long amount);

		long	get_id() const;
		long	get_balance() const;
		long	get_debt() const;

		long	set_balance(long amount);
};

std::ostream &operator<<(std::ostream &os, const Account &obj);

#endif