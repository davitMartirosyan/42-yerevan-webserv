/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCore.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:47:02 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/23 23:57:56 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerCore.hpp"

int ServerCore::getClientBodySize( void )
{
	return (client_body_size);
}

void ServerCore::pushIndex(std::string const &fileNameExample)
{
	index.push_back(fileNameExample);
}

void ServerCore::pushMethods(std::string const &method)
{
	std::string capitalized = method;
	for(size_t i = 0; i < method.size(); i++)
		capitalized[i] = std::toupper(capitalized[i]);
	methods.push_back(capitalized);
}

std::vector<std::string> ServerCore::getIndexFiles( void ) const
{
	return (this->index);
}

std::vector<std::string> ServerCore::getMethods( void ) const
{
	return (this->methods);
}

void ServerCore::setRoot(std::string const &root)
{
	this->root = root;
}

std::string const &ServerCore::getRoot( void ) const
{
	return (this->root);
}

const char* ServerCore::findIndex(std::string const &filename) const
{
	size_t i = 0;
	for(; i < index.size(); i++)
		if (index[i] == filename)
			return (index[i].c_str());
	return (NULL);
}

const char* ServerCore::findMethod(std::string const &method) const
{
	size_t i = 0;
	for(; i < methods.size(); i++)
		if (methods[i] == method)
			return (methods[i].c_str());
	return (NULL);
}

const char* ServerCore::findErrorPage(std::string const &status_code)
{
	std::map<std::string, std::string>::iterator it = error_page.find(status_code);
	if (it != error_page.end())
		return (it->second.c_str());
	return (NULL);
}

void ServerCore::setAutoindex(std::string const &sw)
{
	(sw == "on") ? this->autoindex = 1 : this->autoindex = 0;
}

void ServerCore::pushErrPage(std::string const &key, std::string const &errpage_filename)
{
	error_page.insert(std::make_pair(key, errpage_filename));
}

void ServerCore::setSize(unsigned long long int bodySize)
{
	client_body_size = bodySize;
}

bool ServerCore::getAutoindex( void ) const
{
	return (autoindex);
}