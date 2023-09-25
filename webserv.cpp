/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:33:26 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/26 00:09:47 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"
#define PORT 8080
std::string responseBody( void );

int main(int ac, const char**av, const char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	
	// std::string t1 = "www.example.com:80/res/page1.php?link=http://about.com#account";
	// std::string t2 = "https://www.facebook.com:443/res/page1.php?user=bob#account";
	// std::string t3 = "http://www.example.com/";
	// std::string t4 = "ftp://www.example.com/res/page1.php?user=bob#account";
	// std::string t5 = "www.example.com";
	// std::string t6 = "example.com";
	// Urlx url(t4);
	// std::cout << url.domain() << std::endl;
	
	std::string httpRequest;
	int server_socket, accept_socket;
	size_t valread;
	(void)valread;
	struct sockaddr_in addr;
	int opt = 1;
	int len = sizeof(addr);
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

		bind(server_socket, (struct sockaddr*)&addr, sizeof(addr));
		std::string response;	
		listen(server_socket, 3);
	char http[1024] = {0};
	std::string content;
	while (1)
	{
		accept_socket = accept(server_socket, (struct sockaddr*)&addr, (socklen_t*)&len);
		valread = read(accept_socket, http, 1024);
		
		std::cout << http << std::endl;
		response += "HTTP/1.1 200 OK\r\n";
		response += "Content-Type: text/html\r\n\r\n";
		response += responseBody();
		response += "\r\n";
		send(accept_socket, response.c_str(), response.size(), 0);
		response.clear();
		close(accept_socket);
	}
}


std::string responseBody( void )
{
	std::fstream index;
	std::string line;
	std::string content;
	index.open("tmp/www/index.html");
	while (getline(index, line, '\0')){
		content += line;
	}
	index.close();
	return (content);
}