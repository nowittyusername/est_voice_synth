#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sound_play/sound_play.h>
#include <cstdlib>
#include <sstream>
#include <fstream>


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "talker");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  //sound_play::SoundClient sc;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(0.1);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "Tere, maailm " << count;
    //ss << "Jupiteri suuruselt neljas kuu Europa paiskab tõepoolest võimsaid veepahvakuid maailmaruumi ";
    /*ss << "Jupiteri suuruselt neljas kuu Europa paiskab vist tõepoolest aeg-ajalt võimsaid veepahvakuid maailmaruumi. Veepurskamise kahtlus sai uut tugevat kinnitust, kui teadlased vaatasid hoolikalt läbi andmed, mille NASA kosmoseaparaat Galileo enam kui kakskümmend aastat tagasi toimunud möödalennul kogus. Sellisel juhul aga pidi vesi Europalt paiskuma välja lausa mitmesaja kilomeetri kaugusele kosmose avarusse ";*/
    /*ss << "Jupiteri suuruselt neljas kuu Europa paiskab vist tõepoolest võimsaid veepahvakuid maailmaruumi. Veepurskamise kahtlus sai uut tugevat kinnitust, kui teadlased vaatasid hoolikalt läbi andmed, mille NASA kosmoseaparaat Galileo enam kui kakskümmend aastat tagasi toimunud möödalennul kogus. Sellisel juhul aga pidi vesi Europalt paiskuma välja lausa mitmesaja kilomeetri kaugusele kosmose avarusse. Viimasel ajal on suurte veepursete märke Europal leidnud ka kosmoseteleskoop Hubble. Mõned teadlased on väitnud, et Europa, mille jääkoore all laiub suur veeookean, on üks Päikesesüsteemi paljutõotavamaid paiku, kust võiksime leida kohalikke elusolendeid. Veepursked annavad võimaluse neid spekulatsioone kontrollida, sest tulevased kosmoseaparaadid saaksid neist piisapilvedest proove võtta, millest elu märke otsida ";*/
    msg.data = ss.str();
    
    /*std::ofstream f("/home/jan/synthts_et-master/synthts_et/in.txt");
    f << "Tere, maailm " << count;
    f.close();*/

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    /*system("sh /home/jan/synthts_et-master/synthts_et/convert.sh");
    //sc.playWaveFromPkg("sound_play", "sounds/BACKINGUP.ogg");
    sc.playWaveFromPkg("sound_play", "/home/jan/synthts_et-master/synthts_et/out_tnu.wav");*/
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
