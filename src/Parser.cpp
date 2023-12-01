/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:30:12 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/02 00:39:16 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(std::string const &confFile)
{
    IO.open(confFile.c_str(), std::ios::out);
    if (!IO.is_open())
        throw HTTPCoreException("Error: File not found");
}

Parser::~Parser()
{
    
}