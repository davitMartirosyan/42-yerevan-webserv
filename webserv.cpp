/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:33:26 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/28 19:37:15 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"
#define PORT 8080
std::string responseBody(std::string body);

int main(int ac, const char**av, const char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	
	int server_socket, accept_socket;
	size_t valread;
	(void)valread;
	struct sockaddr_in addr;
	int opt = 1;
	int len = sizeof(addr);
	char http[1024] = {0};
	std::string response;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	bind(server_socket, (struct sockaddr*)&addr, sizeof(addr));
	listen(server_socket, 3);
	while (1)
	{
		accept_socket = accept(server_socket, (struct sockaddr*)&addr, (socklen_t*)&len);
		valread = read(accept_socket, http, 1024);
		std::string request = http;
		/////////Parsing Request/////////////
		/////////////////////////////////
		HttpRequest req(request);///////////
		////////////////////////////
		//////////////////////////
		response += "HTTP/1.1 200 OK\r\n";
		response += "Content-Type: text/html\r\n\r\n";
		response += responseBody("tmp/www/index.html");
		response += "\r\n";
		send(accept_socket, response.c_str(), response.size(), 0);
		response.erase();
		close(accept_socket);
	}
}


std::string responseBody(std::string body)
{
	std::fstream index;
	std::string line;
	std::string content;
	index.open(body.c_str());
	while (getline(index, line, '\0')){
		content += line;
	}
	index.close();
	return (content);
}