#ifndef NETWORK_HXX
# define NETWORK_HXX

# include <core/network/Network.hh>

inline
void Network::readHeaderHandler(Packet& packet, Client* client
  , boost_socket* sock, const boost::system::error_code& error)
{
  if (error)
    return;
  int size = packet.GetData()[0];
  size = (size << 4) | packet.GetData()[1];
  size = (size << 4) | packet.GetData()[2];
  size = (size << 4) | packet.GetData()[3];
  sock->async_read_some(boost::asio::buffer(packet.GetData(), size)
    , boost::bind(&Network::readBodyHandler, this, packet, client, sock
      , boost::asio::placeholders::error));
}

inline
void Network::readBodyHandler(Packet& packet, Client* client, boost_socket* sock
  , const boost::system::error_code& error)
{
  if (error)
    return;
  routing(packet, client);
  Packet newPacket = Packet();
  sock->async_read_some(boost::asio::buffer(newPacket.GetData(), 4)
    , boost::bind(&Network::readHeaderHandler, this, newPacket, client, sock
      , boost::asio::placeholders::error));
  
}

inline
void Network::launchAsyncRead(Client* client)
{
  for (auto& sock : client->getSockets())
  {
    Packet packet = Packet();
    sock.async_read_some(boost::asio::buffer(packet.GetData(), 4)
      , boost::bind(&Network::readHeaderHandler, this, packet, client, &sock
        , boost::asio::placeholders::error));
  }
}

#endif /* NETWORK_HXX */
