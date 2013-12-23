Chat-Program
============

CS6390.003 Advanced Computer Networks Project





/*Server Part Code*/
packagechatroom;

importjava.io.IOException;
importjava.net.DatagramPacket;
importjava.net.DatagramSocket;
importjava.net.InetAddress;
importjava.net.SocketAddress;
importjava.net.SocketException;
importjava.net.UnknownHostException;
importjava.util.Enumeration;
importjava.util.Hashtable;
importjava.util.Scanner;
importjava.util.Date;
importjava.text.SimpleDateFormat;

public class Server implements Runnable{
privateDatagramSocket server = null;
privateDatagramPacketgetDatas = null;
privateInetAddressserverAddress = null;
privateint port = 0;

privatebooleanbeStart = false;
privateboolean test = true;
privateHashtable<String,SocketAddress>infoMemory = new Hashtable<String,SocketAddress>();

publicbooleantestServer(String ip,int port) 
{
this.initServer(ip, port);
return test;
}

public void initServer(String ip,int port) {
this.fixServerLink(ip,port);
try {
server = new DatagramSocket(this.port,serverAddress);
System.out.println("!-The Server Initialization Success！");
beStart = true;
} catch (SocketException s) {
test = false;
errorTip("!-The Server Initialization Fail!");
}
}
private void fixServerLink(String ip,int port) {
if(port == 0)
this.port = 9999;
else
this.port = port;
try {
if(ip.equalsIgnoreCase("0"))
this.serverAddress = InetAddress.getLocalHost();
else
this.serverAddress = InetAddress.getByName(ip);
} catch (UnknownHostException u) {
errorTip("!-Sorry, IP address you put is not currect!");
}
}
public void listenLink() {
byte[] buf = new byte[1024];
String mes = null;
try {
getDatas = new DatagramPacket(buf,buf.length);
System.out.println("!-The Server starts listenning to message.");
while(beStart) {
server.receive(getDatas);
mes = new String(buf,0,getDatas.getLength());
this.analyseMes(mes);
}
} catch (IOException e) {
errorTip("!-The Server Can not receive message");
}
}
private void analyseMes(String mes) {
SocketAddressadr = getDatas.getSocketAddress();
SimpleDateFormatdf = new SimpleDateFormat("yyyy-MM-ddHH:mm:ss");
if(mes.trim().equalsIgnoreCase("-test")) {
transforMesSingle(adr,"-test: !-From Server:Succeed in Testing.");
}
else if(mes.trim().equalsIgnoreCase("-quit")) 
{
String name = this.getConsumerName(adr);
System.out.println(name+"//"+adr+" quit! ");
transforMes("* "+name+" has left the chatroom");
infoMemory.remove(name);
}
else if(mes.trim().equals("-getList"))
 {
StringBuffer list = new StringBuffer();
list.append("-getList,");
Enumeration<String> names = infoMemory.keys();
while (names.hasMoreElements()) {
list.append(names.nextElement()+",");
}
transforMes(list.toString());
}
else if(mes.indexOf("-to ") != -1 &&mes.startsWith("-to "))
 {
String main = mes.substring("-to ".length(),mes.length());
String toName = main.substring(0,main.indexOf(" "));
String name = this.getConsumerName(adr);
String con = name+" say to you :"+main.substring(toName.length()+1,main.length());
if(!infoMemory.containsKey(toName))
transforMesSingle(adr,
"!-The message can not be recevie by whom you send for,please check out.");
else
transforMesSingle(infoMemory.get(toName),con+"   "+df.format(new Date()));
}
else if(mes.indexOf("-nick ") != -1 &&mes.startsWith("-nick "))
 {
String nickName = mes.substring("-nick ".length(), mes.length());
infoMemory.put(nickName,adr);
transforMes("Welcome "+nickName +" joining chatroom!");
System.out.println(nickName+"//"+adr.toString()+"connected");
}
else {
String name = this.getConsumerName(adr);
transforMes(name+": "+mes+"   "+df.format(new Date()));
}
}
private String getConsumerName(SocketAddresssa) {
Enumeration<String> names = infoMemory.keys();
String name = null;
while (names.hasMoreElements()) {
String temp = names.nextElement();
SocketAddressadrs = infoMemory.get(temp);
if (sa.equals(adrs)) {
name = temp;
break;
}
}
return name;
}
public void transforMes(String mes) {
byte[] buf = mes.getBytes();
DatagramPacketsendDatas = null;
Enumeration<SocketAddress> all = infoMemory.elements();
try {
while (all.hasMoreElements()) {
sendDatas = new DatagramPacket(buf,buf.length,all.nextElement());
server.send(sendDatas);
}
} catch (SocketException s) {
errorTip("!-The feedback address is error!");
} catch (IOExceptioni) {
errorTip("!-Can not send message!");
}
}

public void transforMesSingle(SocketAddressadr,Stringmes) {
byte[] buf = mes.getBytes();
try {
DatagramPacketsendDatas = new DatagramPacket(buf,buf.length,adr);
server.send(sendDatas);
} catch (SocketException s) {
errorTip("!-The feedback address is error!");
} catch (IOExceptioni) {
errorTip("!-Can not send message!");
}
}

public void cutServer() {
beStart = false;
if(server != null)
server.close();
System.out.println("!-The server is done.");
}

public void run() {
listenLink();
}


public static void main(String[] args) {
Server ser = new Server();
String getIp = null;
intgetPort = 0;
@SuppressWarnings("resource")
Scanner input = new Scanner(System.in);


boolean goon = true;
while (goon){
System.out.println("1.PLZ input IP address,default address is 0：");
getIp = input.next();
System.out.println("2.PLZ input server port，default port is 0：");
try {
getPort = input.nextInt();
} catch (Exception e) {
System.out.println("!-The port style is not currect!");
}

System.out.println("!-Creating server and running...");
if (ser.testServer(getIp, getPort)) {
new Thread(ser).start();
goon = false;
} else
System.out.println("!-Create server failed！");
}
}

public static void errorTip(String str) {
System.out.println("-----------------n"+str+"n-----------------");
}
}
