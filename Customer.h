/*Consumer Part Code*/
packagechatroom;

importjava.awt.GridLayout;
importjava.awt.event.ActionEvent;
importjava.awt.event.ActionListener;
importjava.awt.event.KeyAdapter;
importjava.awt.event.KeyEvent;
importjava.awt.event.WindowAdapter;
importjava.awt.event.WindowEvent;
import java.io.*;
import java.net.*;
importjava.util.ArrayList;
importjava.util.Scanner;
importjavax.swing.JButton;
importjavax.swing.JFrame;
importjavax.swing.JLabel;
importjavax.swing.JOptionPane;
importjavax.swing.JPanel;
importjavax.swing.JPasswordField;
importjavax.swing.JTextArea;
importjavax.swing.JTextField;

public class Consumer implements Runnable{
privateInetAddresssendAddress = null;
privateint port = 0;
privateDatagramSocket client = null;
privateDatagramPacketsendDatas = null;
privateboolean test = true;
static final JTextArea jt10 = new JTextArea();
static final JTextArea jt3 = new JTextArea();
ArrayList<String>abc= new ArrayList<String>();
ArrayList<String>def= new ArrayList<String>();

/*Login*/
public  void Login(){
finalJFramejf = new JFrame("Client");
JPaneljp = new JPanel();
JLabel jl1 = new JLabel("Username：");
JLabel jl2 = new JLabel("Password：");
JButton but1 = new JButton("Register");
finalJButton but2 = new JButton("Login");
finalJTextField name = new JTextField(8);
finalJPasswordFieldpwd = new JPasswordField(8);
jp.setLayout(new GridLayout(3,2));

jp.add(jl1);
jp.add(name);
jp.add(jl2);
jp.add(pwd);
jp.add(but2);
jp.add(but1);
jf.add(jp);

jf.setSize(300,150);
jf.setLocation(300,200);
jf.setVisible(true);
jf.setResizable(false);
name.addKeyListener(new KeyAdapter(){
public void keyPressed(KeyEvent e){
if((e.getKeyCode() == KeyEvent.VK_ENTER))  /*when type”ENTER”, do Button2 automatically*/
{but2.doClick();}
}
});
pwd.addKeyListener(new KeyAdapter(){
public void keyPressed(KeyEvent e){
if((e.getKeyCode() == KeyEvent.VK_ENTER))
{but2.doClick();}
}});
but1.addActionListener(new ActionListener() {
@Override
public void actionPerformed(ActionEvent e) {
Registor();
}
});
but2.addActionListener(new ActionListener() {
@Override
public void actionPerformed(ActionEvent g) {
String Id = name.getText();
@SuppressWarnings("deprecation")
String Pwd = pwd.getText();

int flag=0;
File f=new File("C://user.txt");
if(!f.exists()){
try {
f.createNewFile();
} catch (IOException e) {
e.printStackTrace();
}
}
FileReaderfr;
try {
fr = new FileReader("C://user.txt");
BufferedReaderbr = new BufferedReader(fr);
try {
String line = br.readLine();
String[] st=null;
inti=0;
while(line!=null){
st = line.split("-");
def.add(st[i]);
def.add(st[i+1]);
line = br.readLine();
st=null;
}
for(int j=0;j<def.size()/2;j++){
if(Id.equals(def.get(2*j)))
{
if(Pwd.equals(def.get(2*j+1)))
{flag=1;}
}
}
} catch (IOException e) {
e.printStackTrace();
}
} catch (FileNotFoundException e1) {
e1.printStackTrace();
}
if(flag==1)
{
send(Id);
jf.dispose();
}
else {JOptionPane.showMessageDialog(null, "Wrong Username or password!"+"\n");
name.setText(null);
pwd.setText(null);
}
}
});}
public void connectServer(String ip,int port) {
this.fixServerLink(ip,port);
try {
client = new DatagramSocket();
} catch (SocketException e) {
System.out.println("The Connection of server is error.");
}
}
private void fixServerLink(String ip,int port) {
if(port == 0)
this.port = 9999;
else
this.port = port;
try {
if(ip.equalsIgnoreCase("0"))
this.sendAddress = InetAddress.getLocalHost();
else
this.sendAddress = InetAddress.getByName(ip);
} catch (UnknownHostException e) {
System.out.println("Sorry, IP address you put is not currect!");
}
}

public void disconnectServer() {
this.sendMes("-quit");
if(client != null){
client.close();
}
}

public void sendMes(String mes) {
byte[] buf = mes.getBytes();
sendDatas = new DatagramPacket(buf,buf.length,sendAddress,port);
test = true;
try {
client.send(sendDatas);
} catch (NullPointerException n) {
test = false;
System.out.println("Can not fetch the message");
} catch (IOException s) {
test = false;
System.out.println("Can not send to server");
}
}
public void getMes() {
byte[] buf = new byte[1024];
DatagramPacketgetDatas = new DatagramPacket(buf,buf.length);
String mes = null;
sendMes("-getList");
try {
while(true) {
client.receive(getDatas);
mes = new String(buf,0,getDatas.getLength());
if(mes.indexOf("-getList") == 0)
this.getList(mes);
else{
jt10.append(mes+"\n");
int a=jt10.getDocument().getLength();
if (a>300)
{
jt10.setText(null);
jt10.append(mes+"\n");
}
System.out.println(mes);
}
}
} catch (IOExceptioni) {
System.out.println("Fail in receving message");
}
}
public String getMesOnce() {
byte[] buf = new byte[1024];
DatagramPacketgetDatas = new DatagramPacket(buf,buf.length);
String mes = null;
try {
client.receive(getDatas);
mes = new String(buf,0,getDatas.getLength());
} catch (Exception e) {
System.out.println("!-Can not receive the message!");
} 
finally {
}
returnmes;
}

private void getList(String mes) {
String[] list = mes.split(",");
jt3.setText("");
for(inti = 1;i<list.length;i++)
{
jt3.append("----"+list[i]+"---"+"\n");}
jt3.paintImmediately(jt3.getX(), jt3.getY(), jt3.getWidth(), jt3.getHeight());
}
publicbooleantestConnect(String ip,int port) {
this.connectServer(ip,port);
this.sendMes("-test");
if (test) {
String mes = this.getMesOnce();
if (mes.startsWith("-test")) {
test = true;
}
}
if(client != null) {
client.close();
}
return test;
}
public void helpList() {JOptionPane.showMessageDialog(null, "What you need to know: If you successfully connnected to the server, all online users could see your message."+"\n");
}

public void run() 
{
getMes();
}
@SuppressWarnings("static-access")
public void send(String Id){
final Consumer consumer = new Consumer();
String getIp = null;
intgetPort = 0;
final Scanner input = new Scanner(System.in);
booleangoahead = true;
while(goahead){
getIp = "0";
getPort = 0;
System.out.println("!-Connecting to server,PLZ wait");
if(consumer.testConnect(getIp,getPort)) {
System.out.println("!-Connected！");
goahead = false;
} 
else
System.out.println("!-Connection failed!");
}
consumer.connectServer(getIp,getPort);
consumer.sendMes("-nick "+Id);
finalJFramejf = new JFrame();
jf.setResizable(false);
JPaneljp = new JPanel();

finalJButton but = new JButton("Send");
but.setToolTipText("Press Ctrl+Enter to send message");

JButton but3 = new JButton("Help!");
finalJTextArea jt2 = new JTextArea();
JLabel j = new JLabel("Online users");
JLabel j2 = new JLabel("********************************************************************************");
jp.setLayout(null);
jp.add(but);
jp.add(but3);
jp.add(consumer.jt10);
jp.add(jt2);
jp.add(j);
jp.add(j2);
jp.add(jt3);

but.setBounds(340,360,80,30);
but3.setBounds(500,360,70,30);
consumer.jt10.setBounds(0,0,400,180);
j2.setBounds(0,180,400,20);
jt2.setBounds(0,200,400,150);
j.setBounds(410,0,180,20);
jt3.setBounds(410,30,160,320);
jf.add(jp);
jf.setSize(600,450);
jf.setVisible(true);

new Thread(consumer).start();
jf.addWindowListener(new WindowAdapter(){
public void windowClosing(WindowEventev){
consumer.disconnectServer();
jf.dispose();
}
});

jt2.addKeyListener(new KeyAdapter(){
public void keyPressed(KeyEvent e){
if((e.getKeyCode() == KeyEvent.VK_ENTER)
&& (e.isControlDown()))
{but.doClick();
jt2.setText("");
}
}
});

but.addActionListener(new ActionListener() {
@Override
public void actionPerformed(ActionEvent e) {
String mes =null;
if(!((mes=jt2.getText()).equalsIgnoreCase("-quit"))) 
{
if (mes.trim().equalsIgnoreCase("-getList")) {
consumer.sendMes(mes);
} 
else if (mes.startsWith("-nick "))
 {
System.out.println("!-You have named, Can not allowed to rename!");
}
else if (mes.equals("")) {
} else {
consumer.sendMes(mes);
jt2.setText("");
}
}else{
consumer.disconnectServer();
}
input.close();
}
});

but3.addActionListener(new ActionListener() {
@Override
public void actionPerformed(ActionEvent arg0) {
consumer.helpList();
}
});
}

/*REGISTER*/
public void Registor(){
finalJFramejf = new JFrame("Register");
JPaneljp = new JPanel();

jp.setLayout(new GridLayout(4,3));

JLabel j1 = new JLabel("User name：");
JLabel j2 = new JLabel("Password：");
JLabel j3 = new JLabel("Re-enter Password：");
JLabel j4 = new JLabel();
finalJLabel j5 = new JLabel();
finalJLabel j6 = new JLabel();
finalJLabel j7 = new JLabel();
finalJTextField name = new JTextField(8);
finalJPasswordFieldpwd = new JPasswordField(8);
finalJPasswordFieldpwd_ag = new JPasswordField(8);
finalJButton but = new JButton("Registor");
JPanel jp1 = new JPanel();
jp1.setLayout(new GridLayout(1,3));
jp1.add(j5);
jp1.add(but);
jp.add(j1);
jp.add(name);
jp.add(j5);
jp.add(j2);
jp.add(pwd);
jp.add(j6);
jp.add(j3);
jp.add(pwd_ag);
jp.add(j7);
jp.add(j4);
jp.add(jp1);
jf.add(jp);

jf.setSize(300,150);
jf.setLocation(300,200);
jf.setVisible(true);
jf.setResizable(false);

but.addActionListener(new ActionListener() {
@Override
public void actionPerformed(ActionEvent g) {
String u_name = name.getText();
String u_pwd = new String(pwd.getPassword());
String u_pwd_ag =new String(pwd_ag.getPassword());
int x=0;
int y=0;
File f=new File("C://user.txt");
if(!f.exists()){
try {
f.createNewFile();
} catch (IOException e) {
e.printStackTrace();
}}
FileReaderfj;
try {
fj = new FileReader("C://user.txt");
BufferedReaderbz = new BufferedReader(fj);
try {
String line = bz.readLine();
if(line==null)
{y=1;}

String[] st=null;
inti=0;
while(line!=null){

st = line.split("-");

abc.add(st[i]);
abc.add(st[i+1]);
line = bz.readLine();
st=null;
}
if(abc.size()==0)
{
x=1;
}
for(int j=0;j<abc.size()/2;j++)
{
if(u_name.equals(abc.get(2*j)))
{ JOptionPane.showMessageDialog(null, "duplicate User name are not allowed, re-enter plz!"+"\n");
name.setText(null);
pwd.setText(null);
pwd_ag.setText(null);
break;
}
if(!u_pwd.equals(u_pwd_ag))
{JOptionPane.showMessageDialog(null, "Password are not the same!"+"\n");
pwd.setText(null);
pwd_ag.setText(null);
break;
}
if(j==(abc.size()/2-1))
x=1;
}
} catch (IOException e) {
e.printStackTrace();
}
} catch (FileNotFoundException e1) {
e1.printStackTrace();
}
if(x==1)
{try {
FileWriterfw=new FileWriter(f,true);
BufferedWriterjs=new BufferedWriter(fw);
if(y==1){}
else{js.newLine();}
js.write(u_name+"-"+u_pwd);
js.close();
fw.close();
JOptionPane.showMessageDialog(null, "New user added!"+"\n");
jf.dispose();
} catch (IOException e) {
e.printStackTrace();
}
}
}
} );
}
/* Main Function*/
public static void main(String args[])
{
Consumer c = new Consumer();
c.Login();
}}
