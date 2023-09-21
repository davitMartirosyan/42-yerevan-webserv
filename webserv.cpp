/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:33:26 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/22 01:16:22 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"

int main(int argc, const char**argv, const char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	std::string t1 = "www.example.com:80/res/page1.php?user=bob#account";
	std::string t2 = "https://www.example.com/res/page1.php?user=bob#account";
	std::string t3 = "http://www.example.com/";
	std::string t4 = "www.example.com/res/page1.php?user=bob#account";
	std::string t5 = "www.example.com";
	std::string t6 = "example.com";
	
	Urlx url(t1);
	std::cout << url.getProto() << std::endl;
}
