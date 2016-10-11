import java.util.Scanner;
import java.io.*;

class B10
{
	public static void main(String args[])
	{
		int req; /* number of requests to be sent*/
		int t; /* time period*/
		float lamda;  /*arrival rate in seconds= req/t */
		float u; /* service time in milli seconds */
		float p; /* utilization = arrival time/ service time*/
		float r; /* throughput = utilization * service time*/
		float L, Lq; /* average requests in the system and queue*/
		float W, Wq; /* average waiting time in the system and queue*/

		Scanner in = new Scanner(System.in);
		System.out.println("Program to calculate utilization and throughput");
		System.out.println("Enter the number of requests to be sent");
		req = in.nextInt();
		System.out.println("Number of requests to be sent =" + req);
		System.out.println("Enter a time period in seconds");
		t = in.nextInt();
		System.out.println("Time period =" + t);
		lamda = req / t;
		System.out.println("Arrival rate is =" + lamda);
		System.out.println("Enter a time required to service a request in milli seconds");
		u = in.nextFloat();
		u = u/1000;
		System.out.println("Service time =" + u);
		p = (lamda / u) / 1000; /* channel utilization in a range of 0-1*/
		System.out.println("Channel Utilization is =" + p);
		r = (p * u) / 1000; /* throughput in a range of 0-1*/
		System.out.println("Throughput is =" + r);
	}
}
