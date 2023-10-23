/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_core_module_conf.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:47:02 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/23 23:57:56 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_core_module_conf.hpp"

int http_core_module_conf::getClientBodySize( void )
{
	return (client_body_size);
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

const char* http_core_module_conf::findIndex(std::string const &filename) const
{
	size_t i = 0;
	for(; i < index.size(); i++)
		if (index[i] == filename)
			return (index[i].c_str());
	return (NULL);
}

const char* http_core_module_conf::findMethod(std::string const &method) const
{
	size_t i = 0;
	for(; i < methods.size(); i++)
		if (methods[i] == method)
			return (methods[i].c_str());
	return (NULL);
}

const char* http_core_module_conf::findErrorPage(std::string const &status_code)
{
	std::map<std::string, std::string>::iterator it = error_page.find(status_code);
	if (it != error_page.end())
		return (it->second.c_str());
	return (NULL);
}

void http_core_module_conf::setAutoindex(std::string const &sw)
{
	(sw == "on") ? this->autoindex = 1 : this->autoindex = 0;
}

void http_core_module_conf::pushErrPage(std::string const &key, std::string const &errpage_filename)
{
	error_page.insert(std::make_pair(key, errpage_filename));
}

void http_core_module_conf::setSize(unsigned long long int bodySize)
{
	client_body_size = bodySize;
}

bool http_core_module_conf::getAutoindex( void ) const
{
	return (autoindex);
}