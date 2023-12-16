/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:38:14 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/24 23:21:13 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location(std::string const &location)
{
	this->location = location;
}

Location::~Location()
{
	
}

void Location::setRedirection(int status, std::string redirectPath)
{
	redirection.insert(std::make_pair(status, redirectPath));
}

std::map<int, std::string> const &Location::getRedirection( void ) const
{
	return (redirection);
}

std::string const &Location::getLocation( void ) const
{
	return (this->location);
}