/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkScanner.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:02:09 by msaadidi          #+#    #+#             */
/*   Updated: 2024/10/25 16:23:14 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetworkScanner.hpp"

NetworkScanner::NetworkScanner(){}

NetworkScanner::NetworkScanner(const std::string& _IpStart, const std::string& _IpEnd) : IpStart(_IpStart), IpEnd(_IpEnd){}

NetworkScanner::~NetworkScanner(){}

NetworkScanner& NetworkScanner::operator=(const NetworkScanner& N)
{
    if (this == &N) return *this;
    IpStart = N.IpStart;
    IpEnd = N.IpEnd;
    return *this;
}

NetworkScanner::NetworkScanner(const NetworkScanner& N)
{
    *this = N;
}

int     NetworkScanner::calcPortion(std::string& sIp, std::string& eIp)
{
    std::istringstream   sStream(sIp), eStream(eIp);
    std::string         sByte, eByte;
    int matchedBytes = 0;
    while (std::getline(sStream, sByte, '.') && std::getline(eStream, eByte, '.'))
    {
        if (sByte == eByte)
            matchedBytes++;
        else 
            break ;
    }
    return (0);

}

void    NetworkScanner::pingHost(std::string& Ip)
{
    std::string command = "ping -c 1 " + Ip + " > /dev/null 2>&1";
    int result = system(command.c_str());
    if (result)
        results.push_back(Ip + " is reachable\n");
    else
        results.push_back(Ip + "is not reachable\n");
}

void    NetworkScanner::scanPort(std::string& Ip, int port)
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in  host_addr;
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    inet_pton(AF_INET, Ip.c_str(), &host_addr.sin_addr);
    int result = connect(socketfd, (struct sockaddr *)&host_addr, sizeof(host_addr));
    if (result)
        results.push_back(std::to_string(port) + " is open in " + Ip);
    else
        results.push_back(std::to_string(port) + " is closed in " + Ip);
    close(socketfd);
}


void    NetworkScanner::outputResults()
{
    for (size_t i = 0; i < results.size(); i++)
        std::cout << results[i] << std::endl;
}

void    NetworkScanner::scanNetwork()
{
    int Portion = calcPortion(IpStart, IpEnd);
    for (int i = 0; i < 4 - Portion; i++)
    {
        //ping reachable hosts and ports
    }
}
