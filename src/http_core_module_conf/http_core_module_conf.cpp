/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_core_module_conf.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:47:02 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/23 12:37:16 by dmartiro         ###   ########.fr       */
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
	std::string capitalized = method;
	for(size_t i = 0; i < method.size(); i++)
		capitalized[i] = std::toupper(capitalized[i]);
	methods.push_back(capitalized);
}

std::vector<std::string> http_core_module_conf::getIndexFiles( void ) const
{
	return (this->index);
}

std::vector<std::string> http_core_module_conf::getMethods( void ) const
{
	return (this->methods);
}

void http_core_module_conf::setRoot(std::string const &root)
{
	this->root = root;
}

std::string const &http_core_module_conf::getRoot( void ) const
{
	return (this->root);
}

const char* http_core_module_conf::findIndexFile(std::string const &filename) const
{
	size_t i = 0;
	for(; i < index.size(); i++)
		if (index[i] == filename)
			return (index[i].c_str());
	return (NULL);
}