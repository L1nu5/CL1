#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ServerExample");
int main (int argc, char *argv[])

   {
    bool verbose = true;
    uint32_t nCsma = 3;

  	// AnimationInterface anim ("animation.xml");
	// anim.EnablePacketMetadata (true);
    CommandLine cmd;
	cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
	cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
	cmd.Parse (argc,argv);
  

   if (verbose)

     {
        LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);

        LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
      }
  nCsma = nCsma == 0 ? 1 : nCsma;

  NodeContainer p2pNodes1;
  p2pNodes1.Create (2);

  NodeContainer p2pNodes2;
  p2pNodes2.Create (2);

  NodeContainer p2pNodes3;
  p2pNodes3.Create (2);

  NodeContainer csmaNodes1;
  csmaNodes1.Add (p2pNodes1.Get (1));
  csmaNodes1.Create (nCsma);

  NodeContainer csmaNodes2;
  csmaNodes2.Add (p2pNodes2.Get (1));
  csmaNodes2.Create (nCsma);

  NodeContainer csmaNodes3;
  csmaNodes3.Add (p2pNodes3.Get (1));
  csmaNodes3.Create (nCsma);

 PointToPointHelper PointToPoint1;
 PointToPoint1.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
 PointToPoint1.SetChannelAttribute ("Delay", StringValue ("20ms"));
 
 PointToPointHelper PointToPoint2;
 PointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
 PointToPoint2.SetChannelAttribute ("Delay", StringValue ("10ms"));
 
 PointToPointHelper PointToPoint3;
 PointToPoint3.SetDeviceAttribute ("DataRate", StringValue ("15Mbps"));
 PointToPoint3.SetChannelAttribute ("Delay", StringValue ("5ms"));
 
 NetDeviceContainer p2pDevices1;
 NetDeviceContainer p2pDevices2;
 NetDeviceContainer p2pDevices3;

 p2pDevices1 = PointToPoint1.Install (p2pNodes1);
 p2pDevices2 = PointToPoint2.Install (p2pNodes2);
 p2pDevices3 = PointToPoint3.Install (p2pNodes3);

 CsmaHelper csma1;
 csma1.SetChannelAttribute ("DataRate", StringValue ("10Mbps"));
 csma1.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

 CsmaHelper csma2;

 csma2.SetChannelAttribute ("DataRate", StringValue ("10Mbps"));

 csma2.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (8000)));

 CsmaHelper csma3;

 csma3.SetChannelAttribute ("DataRate", StringValue ("10Mbps"));
 
 csma3.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (9000)));

 NetDeviceContainer csmaDevices1;

 NetDeviceContainer csmaDevices2;

 NetDeviceContainer csmaDevices3;

 csmaDevices1 = csma1.Install (csmaNodes1);

 csmaDevices2 = csma2.Install (csmaNodes2);

 csmaDevices3 = csma3.Install (csmaNodes3);

 InternetStackHelper stack1;

 InternetStackHelper stack2;

 InternetStackHelper stack3;

 stack1.Install (p2pNodes1.Get (0));

 stack2.Install (p2pNodes2.Get (0));

 stack3.Install (p2pNodes3.Get (0));

 stack1.Install (csmaNodes1);

 stack2.Install (csmaNodes2);

 stack3.Install (csmaNodes3);

 Ipv4AddressHelper address1;

 Ipv4AddressHelper address2;
 
 Ipv4AddressHelper address3;

 address1.SetBase ("10.1.1.0", "255.255.255.0");
 address2.SetBase ("10.2.1.0", "255.255.255.0");
 address3.SetBase ("10.3.1.0", "255.255.255.0");

 Ipv4InterfaceContainer p2pInterfaces1;

 Ipv4InterfaceContainer p2pInterfaces2;

 Ipv4InterfaceContainer p2pInterfaces3;

 p2pInterfaces1 = address1.Assign (p2pDevices1);

 p2pInterfaces2 = address2.Assign (p2pDevices2);

 p2pInterfaces3 = address3.Assign (p2pDevices3);

 address1.SetBase ("10.1.2.0", "255.255.255.0");

 address2.SetBase ("10.1.3.0", "255.255.255.0");

 address3.SetBase ("10.1.4.0", "255.255.255.0");

 Ipv4InterfaceContainer csmaInterfaces1;
 
 Ipv4InterfaceContainer csmaInterfaces2;

 Ipv4InterfaceContainer csmaInterfaces3;

 csmaInterfaces1 = address1.Assign (csmaDevices1);

 csmaInterfaces2 = address2.Assign (csmaDevices2);

 csmaInterfaces3 = address3.Assign (csmaDevices3);

 UdpEchoServerHelper echoServer1 (19);

 UdpEchoServerHelper echoServer2 (20);

 UdpEchoServerHelper echoServer3 (21);

ApplicationContainer serverApps1 = echoServer1.Install (csmaNodes1.Get(nCsma));

	serverApps1.Start (Seconds (1.0));

	serverApps1.Stop (Seconds (20.0));

ApplicationContainer serverApps2 = echoServer2.Install (csmaNodes2.Get(nCsma));

	serverApps2.Start (Seconds (1.0));

	serverApps2.Stop (Seconds (20.0));
ApplicationContainer serverApps3 = echoServer3.Install (csmaNodes3.Get(nCsma));

	serverApps3.Start (Seconds (1.0)); 

	serverApps3.Stop (Seconds (20.0));

UdpEchoClientHelper echoClient1 (csmaInterfaces1.GetAddress (nCsma),19);

 echoClient1.SetAttribute ("MaxPackets", UintegerValue (1));

 echoClient1.SetAttribute ("Interval", TimeValue (Seconds (1.0)));

 echoClient1.SetAttribute ("PacketSize", UintegerValue (1024));

UdpEchoClientHelper echoClient2 (csmaInterfaces2.GetAddress (nCsma),20);

 echoClient2.SetAttribute ("MaxPackets", UintegerValue (1));

 echoClient2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));

 echoClient2.SetAttribute ("PacketSize", UintegerValue (1024));

UdpEchoClientHelper echoClient3 (csmaInterfaces3.GetAddress (nCsma),21);

 echoClient3.SetAttribute ("MaxPackets", UintegerValue (1));

 echoClient3.SetAttribute ("Interval", TimeValue (Seconds (1.0)));

 echoClient3.SetAttribute ("PacketSize", UintegerValue (1024));

 

 ApplicationContainer clientApps1= echoClient1.Install (p2pNodes1.Get (0));

 clientApps1.Start (Seconds (2.0));

 clientApps1.Stop (Seconds (10.0));

 ApplicationContainer clientApps2= echoClient2.Install (p2pNodes2.Get (0));

 clientApps2.Start (Seconds (2.0));

 clientApps2.Stop (Seconds (10.0));

 ApplicationContainer clientApps3= echoClient3.Install (p2pNodes3.Get (0));

 clientApps3.Start (Seconds (2.0));

 clientApps3.Stop (Seconds (10.0));

 Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
 PointToPoint1.EnablePcapAll ("abc");

 PointToPoint2.EnablePcapAll ("def");

 PointToPoint3.EnablePcapAll ("ghi");

 csma1.EnablePcap ("abc", csmaDevices1.Get (1), true);
 
 csma2.EnablePcap ("def", csmaDevices2.Get (1), true);

 csma3.EnablePcap ("ghi", csmaDevices3.Get (1), true);

 Ptr<Node> n1 = p2pNodes1.Get (1);
 Ptr<Node> n2 = p2pNodes2.Get (1);
 Ptr<Node> n3 = p2pNodes3.Get (1);
 AnimationInterface anim ("animation.xml");
 //anim.SetMobilityPollInterval (Seconds (1));
 anim.SetConstantPosition (n1, 100, 300);
 anim.SetConstantPosition (n2, 200, 200);
 anim.SetConstantPosition (n3, 400, 200);
 //anim.EnablePacketMetadata (true);
 Simulator::Run ();

 Simulator::Destroy ();

 return 0;

 }
