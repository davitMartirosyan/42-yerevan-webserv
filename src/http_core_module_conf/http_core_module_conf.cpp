/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_core_module_conf.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:47:02 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/22 10:14:55 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_core_module_conf.hpp"

int http_core_module_conf::getClientBodySize( void )
{
	return (client_body_size);
}

std::string const &http_core_module_conf::getRootPath( void )
{
	return (root);
}

void http_core_module_conf::pushIndex(std::string const &fileNameExample)
{
	index.push_back(fileNameExample);
}

void http_core_module_conf::pushMethods(std::string const &method)
{
	std::string capitalized;
	for(size_t i = 0; i < method.size(); i++)
		capitalized[i] = std::toupper(method[i]);
	methods.push_back(capitalized);
}