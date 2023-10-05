/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:03:11 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/06 00:35:40 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"

class ServerException : public std::exception
{
    public:
        ServerException (const char *msg);
        virtual ~ServerException() throw();
        const char* what() const throw();
    private:
        std::string message;
};