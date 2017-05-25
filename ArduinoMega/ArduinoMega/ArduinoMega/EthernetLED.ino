// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
	0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

unsigned int localPort = 1234;						// local port to listen on
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];			//buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";				// a string to send back
// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;


void EthernetUDPHandling(IPAddress remoteIP, int packetSize)
{
	bool sendAnswer = false;
	if (strncmp(packetBuffer,"LED On",packetSize)==0)
	{
		if (Settings.PowerState == false)
		{
			//theLEDs are currently off. Turning on
			Settings.PowerState = true;
			#if defined(DEBUGMODE)
				Serial.println("LAN: Cmd: Led On");
			#endif
			BrightnessTurnOn();
			Settings.ChangesToEffectMade = 1;
		}
		
		sendAnswer = true;
		sprintf(ReplyBuffer, "Done");
	}
	else if (strncmp(packetBuffer, "LED Off",packetSize)==0)
	{
		if (Settings.PowerState == true)
		{
			//theLEDs are currently off. Turning on
			Settings.PowerState = false;
			#if defined(DEBUGMODE)
			Serial.println("LAN: Cmd: Led Off");
			#endif
			EEPROMsave();
			BrightnessTurnOff();
		}
		
		sendAnswer = true;
		sprintf(ReplyBuffer, "Done");
	}
	else //Unknown Command
	{
		sendAnswer = true;
		sprintf(ReplyBuffer, "unkn Command");
	}
	
	if (sendAnswer)
	{
		// send a reply to the IP address and port that sent us the packet we received
		Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
		Udp.write(ReplyBuffer);
		Udp.endPacket();
	}
}

void MainEthernet()
{
	EVERY_N_MILLISECONDS(500)
	{
		//Renew the Lease
		Ethernet.maintain();
	}

	EVERY_N_MILLISECONDS(100)
	{
		int packetSize = Udp.parsePacket();
		if (packetSize)
		{
			IPAddress remote = Udp.remoteIP();					// save the IP Adress of the Sender
			Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);		// read the packet into packetBufffer
			#ifdef DEBUGMODE
				Serial.print("Received packet of size ");
				Serial.println(packetSize);
				Serial.print("From ");
				for (int i = 0; i < 4; i++)
				{
					Serial.print(remote[i], DEC);
					if (i < 3)
						Serial.print(".");
				}
				Serial.print(", port ");
				Serial.println(Udp.remotePort());

				Serial.println("Contents:");
				Serial.println(packetBuffer);
			#endif
			
			//give the Packet to the packet handling fnc
			EthernetUDPHandling(remote, packetSize);
		}
	}
	
	
}

void ConnectEthernet()
{
	// start the Ethernet connection:
	#ifdef DEBUGMODE
		Serial.println("LAN: Trying to get an IP address using DHCP");
	#endif // DEBUG

	if (Ethernet.begin(mac) == 0)
	{
		#ifdef DEBUGMODE
				Serial.println("LAN: Failed to configure Ethernet using DHCP");
		#endif // DEBUGMODE
		// initialize the Ethernet device not using DHCP:
		Ethernet.begin(mac, ip, myDns, gateway, subnet);
	}
	// print your local IP address:
	ip = Ethernet.localIP();
	#ifdef DEBUGMODE
		Serial.print("LAN: My IP address: ");
		for (byte thisByte = 0; thisByte < 4; thisByte++)
		{
			// print the value of each byte of the IP address:
			Serial.print(ip[thisByte], DEC);
			Serial.print(".");
		}
		Serial.println();
	#endif // DEBUGMODE

	Udp.begin(localPort);
}

