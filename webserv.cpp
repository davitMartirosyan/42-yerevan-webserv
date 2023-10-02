/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:33:26 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/02 20:32:17 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"
#include "HttpMetaProvider.hpp"
#include "HTTPServer.hpp"
HttpMetaProvider Meta;

std::string responseBody(std::string body);

int main(int ac, const char**av, const char **env)
{
	HTTPServer server(AF_INET, SOCK_STREAM, 0);
	
	server.bindServer("127.0.0.1", 8080);
	server.startListening(5);
	std::cout << "======== Server started =========" << std::endl;
	while (1)
	{
		
	}
	std::cout << "======== Server stopped =========" << std::endl;
}

std::string responseBody(std::string path)
{
	std::fstream index;
	std::string line;
	std::string content;
	index.open(path.c_str());
	if (index.is_open())
	{
		while (getline(index, line, '\0')){
			content += line;
		}
		index.close();
		return (content);
	}
	return ("<h1>404</h1>");

}
