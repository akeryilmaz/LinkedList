#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "VideoShare.hpp"
#include "User.hpp"

using namespace std;

void VideoShare::printAllVideos() {
    videos.print();
}

void VideoShare::printAllUsers() {
    users.print();
}

/* TO-DO: method implementations below */

VideoShare::VideoShare(){
    LinkedList<User> users;
    LinkedList<Video> video;
}
VideoShare::~VideoShare(){
}
void VideoShare::createUser(const string & userName, const string & name, const string & surname){
    User newUser(userName, name, surname);
    users.insertNode(users.getHead(), newUser);
}

void VideoShare::loadUsers(const string & fileName){
    string line;
    string filename;
    ifstream myfile(fileName.c_str());
    if (myfile.is_open()){
        while (getline (myfile,line)){
            string username, name, surname;
            int firstindex, secondindex;
            firstindex = line.find(";");
            secondindex = line.find(";", firstindex+1);
            username = line.substr(0,firstindex);
            name = line.substr(firstindex+1, secondindex-firstindex-1);
            surname = line.substr(secondindex+1);
            if (username!=""){
            User currentUser(username, name, surname);
            users.insertNode(users.getHead(), currentUser);
            }
        }
    }
    else cout << "Unable to open file";
}

void VideoShare::createVideo(const string & title, const string & genre){
    Video newVideo(title, genre);
    videos.insertNode(videos.getHead(), newVideo);
}
void VideoShare::loadVideos(const string & fileName){
    string line;
    string filename;
    ifstream myfile(fileName.c_str());
    if (myfile.is_open()){
        while (getline (myfile,line)){
            string title, genre;
            int index;
            index = line.find(";");
            title = line.substr(0,index);
            genre = line.substr(index+1);
            if (title!=""){
                Video currentVideo(title, genre);
                videos.insertNode(videos.getHead(), currentVideo);
            }
        }
    }
    else cout << "Unable to open file";
}

void VideoShare::addFriendship(const string & userName1, const string & userName2){
    Node<User> *node1, *node2;
    User *user1, *user2;
    node1 = users.findNode(userName1);
    if (node1 == NULL) return;
    user1 = node1->getDataPtr();
    node2 = users.findNode(userName2);
    if (node2 == NULL) return;
    user2 = node2->getDataPtr();
    user1->addFriend(user2);
    user2->addFriend(user1);
}

User* VideoShare::findUser(string const &userName){
    Node<User> *node;
    User searchUser(userName);
    if (node = users.findNode(searchUser)) return node->getDataPtr();
    else return NULL;
}

Video* VideoShare::findVideo(string const &v_title){
    Node<Video> *node;
    Video searchVideo(v_title);
    if (node = videos.findNode(searchVideo)) return node->getDataPtr();
    else return NULL;
}

void VideoShare::removeFriendship(const string & userName1, const string & userName2){
    User *user1, *user2;
    user1 = findUser(userName1);
    if (user1 == NULL) return;
    user2 = findUser(userName2);
    if (user2 == NULL) return;
    user1->removeFriend(user2);
    user2->removeFriend(user1);
}
void VideoShare::updateUserStatus(const string & userName, Status newStatus){
    User *user;
    user = findUser(userName);
    if (user == NULL) return;
    user->updateStatus(newStatus);
}
void VideoShare::subscribe(const string & userName, const string & videoTitle){
    User *user;
    Video *video;
    user = findUser(userName);
    if (user == NULL) return;
    if (user->getStatus()==SUSPENDED) return;
    video = findVideo(videoTitle);
    if (video == NULL) return;
    user->subscribe(video);
}
void VideoShare::unSubscribe(const string & userName, const string & videoTitle){
    User *user;
    Video *video;
    user = findUser(userName);
    if (user==NULL) return;
    if (user->getStatus()==SUSPENDED) return;
    video = findVideo(videoTitle);
    if (video == NULL) return;
    user->unSubscribe(video);
}
void VideoShare::deleteUser(const string & userName){
    User *toDelete, *deleteFrom;
    LinkedList<User *> *friendsToDelete;
    toDelete = findUser(userName);
    if (toDelete == NULL) return;
    friendsToDelete = toDelete->getFriends();
    while(friendsToDelete->first()){
        deleteFrom = friendsToDelete->first()->getData();
        deleteFrom->removeFriend(toDelete);
        friendsToDelete->deleteNode(friendsToDelete->getHead());
    }
    users.deleteNode(users.findPrev(*toDelete));
}

void sortVideos(LinkedList<Video*> *videos){
    Node<Video*> *currentVideo;
    int n;
    bool sorted = false ;
    n = videos->getLength();
    for (int i=0; (i<n-1) && !sorted; i++) {
        sorted = true;
        currentVideo = videos->first();
        for (int j=1; j<=n-i-1; j++){
            if ((currentVideo->getData()->getTitle()).compare(currentVideo->getNext()->getData()->getTitle())>0) 
            {
                videos->swap(j, j-1); // Swap these two
                sorted = false ; // Mark exchange
            }
            currentVideo = currentVideo->getNext();
        }
    }
}

void VideoShare::sortUserSubscriptions(const string & userName){
    LinkedList<Video*> *subs;
    subs = findUser(userName)->getSubscriptions();
    sortVideos(subs);
}

void VideoShare::printUserSubscriptions(const string & userName){
    User *user;
    user = findUser(userName);
    if (user == NULL) return;
    user->printSubscriptions();
}
void VideoShare::printFriendsOfUser(const string & userName){
    User *user;
    user = findUser(userName);
    if (user == NULL) return;
    user->printFriends();
}
void VideoShare::printCommonSubscriptions(const string & userName1, const string & userName2){
    User *user1, *user2;
    Node<Video*> *subNode1, *subNode2;
    user1 = findUser(userName1);
    Video *vid1, *vid2;
    if (user1 == NULL) return;
    user2 = findUser(userName2);
    if (user2 == NULL) return;
    subNode1 = user1->getSubscriptions()->first();
    subNode2 = user2->getSubscriptions()->first();
    vid1 = subNode1->getData();
    vid2 = subNode2->getData();
    while(subNode1 && subNode2){
        if (vid1 == vid2) {
			cout << *vid1 << endl;
			subNode1 = subNode1->getNext();
			subNode2 = subNode2->getNext();
			}
        else if ((vid1->getTitle()).compare(vid2->getTitle())<0) {
            subNode1 = subNode1->getNext();
            vid1 = subNode1->getData();
        }
        else {
            subNode2 = subNode2->getNext();
            vid2 = subNode2->getData();
        }
    }
}
void VideoShare::printFriendSubscriptions(const string & userName){
    User *user;
    Node<User*> *current;
    Node<Video*> *iterator;
    LinkedList<Video*> toprint;
    user = findUser(userName);
    if (user == NULL) return;
    current = user->getFriends()->first();
    while(current){
        Node<Video*> *currentsub;
        currentsub = current->getData()->getSubscriptions()->first();
        while(currentsub){
            int flag=0;
            iterator = toprint.first();
            while(iterator){
                if((iterator->getData()->getTitle()).compare(currentsub->getData()->getTitle())==0){
                    flag = 1;
                    break;
                }
                iterator = iterator->getNext();
            }
            if (!flag) toprint.insertNode(toprint.getHead(),currentsub->getData());
            currentsub = currentsub->getNext();
        }
        current = current->getNext();
    }
    sortVideos(&toprint);
    iterator = toprint.first();
    while(iterator){
        cout << *(iterator->getData());
        iterator = iterator->getNext();
    }
    cout << endl;
}

bool VideoShare::isConnected_helper(User *user1, User *user2){
    Node<User*> *currentfriend, *currentuser;
    LinkedList<User*> *friends;
    currentuser = traversed.first();
    while(currentuser){
        if((currentuser->getData()->getUsername()).compare(user1->getUsername())==0) return false;
        currentuser = currentuser->getNext();
    }	
    traversed.insertNode(traversed.getHead(), user1);
    friends = user1->getFriends();
    currentfriend = friends->first();
    while(currentfriend){
        if ((currentfriend->getData()->getUsername()).compare(user2->getUsername())==0) return true;
        if (isConnected_helper(currentfriend->getData(), user2)) return true;
        currentfriend = currentfriend->getNext();
    }
    return false;
}

bool VideoShare::isConnected(const string & userName1, const string & userName2){
    User *user1, *user2;
    bool result;
    user1 = findUser(userName1);
    user2 = findUser(userName2);
    if (user1==NULL || user2==NULL) return false;
    result = isConnected_helper(user1, user2);
    traversed.clear();
    return result;
}

