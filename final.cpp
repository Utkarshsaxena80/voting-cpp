    #include<bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist (1000,3000);
int random_int = dist(gen);


void choiced();

void displayMenu();

struct candidateVotes{
    int id;
    int  votes;
    candidateVotes(int i,int v): id(i), votes(v){}
};
struct Compare{
    bool operator()(const candidateVotes&a, const candidateVotes &b){
        return a.votes< b.votes;
    }
};

    priority_queue<candidateVotes,vector<candidateVotes>,Compare> maxHeap; 
    unordered_map<int,int> result;
    int maxVotes=0;
    int leadingCandidate=-1;
    unordered_map<int,bool> alreadyVoted;

    



struct node {
    int data;
    string name;
    node* left;
    node* right;    
    node(int val,string nam):data(val),name(nam), left(nullptr), right(nullptr) {}
};

class BST {
public:
    node* root;
    BST() : root(nullptr) {}
    node* insert(node* node1, int data,string name) {
        if (!node1) return new node(data,name);
        
        if (data < node1->data) {
            node1->left = insert(node1->left, data,name);
        } else if (data > node1->data) {
            node1->right = insert(node1->right, data,name);
        }
        return node1;
    }
    node *search(node * node1,int id){
        if(node1==nullptr|| node1->data==id){
            return node1;
        }
        if(id<node1->data){
            return search(node1->left,id);
        }
        return search(node1->right,id);
    }
   void  displayCandidates(node * root){
    if(root==nullptr){
        return ;
    }
    displayCandidates(root->left);
    cout<<"ID: "<<root->data<<"  Name: "<<root->name<<endl;
    displayCandidates(root->right);
   }

  void reverseTraveral(node* root,vector<int> &elements){
    if(!root) {
        return ;
        }
   reverseTraveral(root->right,elements);
   int d=root->data;
   elements.push_back(d);
   reverseTraveral(root->left,elements);
  }

};

BST b1;
BST b2;
class Node {
public:
    string name;
    int id;
    bool isCandidate; 
    bool isReady; 
    string party; 
    string city;
    Node* next;

    Node(const string& n, int i, bool c, bool r = false, const string& p = "",const string& d="") {
     name=n;
     id=i;
     isCandidate=c;
     isReady = r;
     party=p;
     city=d;
     next=nullptr;
     }
         
};
  Node* head;
class LinkedList {
public:
 
    LinkedList() { head=nullptr; 
    }

    void insert(const string& name, int id, bool isCandidate, bool isReady = false, const string& party="",const string& city="") {
    Node* newNode=new Node(name, id, isCandidate, isReady, party,city);
    if (head==nullptr) { head=newNode;} 
        else {
        Node* temp=head;
        while (temp->next!=nullptr) {
        temp=temp->next;
         }
        temp->next=newNode;
        }
    }
    bool idunique(int id) const {
        Node* temp = head;
        while (temp!=nullptr) {
            if (temp->id==id) return false;
            temp=temp->next;
        }
        return true;
    }
    void displayCandidates() const {
    Node* temp = head;
   
    while (temp != nullptr) {
        if (temp->isCandidate) {
            cout << "Name: " << temp->name << ", ID: " << temp->id << ", Party: " << temp->party << endl;
        }
        temp = temp->next;
    }
}

void displayVoters() const {
    Node* temp = head;
    
    while (temp != nullptr) {
        if (!temp->isCandidate) {
            cout << "Name: " << temp->name << ", ID: " << temp->id << endl;
        
        if (temp->isReady)
                    cout << " (Ready for turn)" << endl;
                else
                    cout << endl;
           
        }
        temp = temp->next;
    }
}

Node* getVoterById(int  id) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->id == id)
                return temp;
            temp = temp->next;
        }
        return nullptr; 
    }
};

    unordered_set<string> cities1;
    LinkedList registrations;
    LinkedList candidateRegsitrations;
class RegistrationSystem {
private:
    stack<string>registrationhis;
    queue<string>registrationqueue;

public:

    void registerVoter() {
        string filename="voters.txt";
        ofstream file(filename);
        if(!file){
            cerr<<"couldnt open file "<<endl;
            return ;
        }
        string name;
        int id;
        cout << "Enter voter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter voter ID: ";
        cin >> id;
        string city;
        cout<< "Enter city : "<<endl;
        cin>>city;
        file<<name<<" "<<id<<" "<<" "<<city<<"\n";
        file.close();

        if (registrations.idunique(id)) {
            registrations.insert(name, id, false,false,"",city);
            registrationhis.push("Voter: " + id);
            registrationqueue.push("Voter: " + id);
            cout << "Voter registered successfully!" << endl;
        } else {
            cout << "ID already exists. Registration failed." << endl;
        }

    } 
    void registerCandidate() {
        string filename="candidates.txt";
        ofstream file(filename,ios::app);
        if(!file){
            cerr<<"error: could not write into file\n";
            return ;
        }
        string name,  party,city;
        int id;
        cout << "Enter candidate name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter candidate ID: ";
        cin >> id;
        cout << "Enter party name: ";
        cin.ignore();
        getline(cin, party);
        cout<<"Enter city ";
        getline(cin,city);
        file<<name<<" "<<id<<" "<<party<<" "<<city<<" "<<"\n";
        file.close();
        if (registrations.idunique(id)) {
            registrations.insert(name, id, true, false, party,city);
            registrationhis.push("Candidate: " + id);
            registrationqueue.push("Candidate: " + id);
            cout << "Candidate registered successfully!" << endl;
        } else {
            cout << "ID already exists. Registration failed." << endl;
        }
       
        auto result= cities1.insert(city);
        cout<<cities1.size();

    }

    void displayAllRegistrations() const {
        cout << "Registered Candidates:" << endl;
        registrations.displayCandidates();
        cout<<endl;
        cout<<"Registered Voters: "<<endl;
        registrations.displayVoters();
    }


    void displayRegistrationHistory() const {
        cout << "Registration History (Most recent first):" << endl;
        stack<string> tempStack = registrationhis;
        while (!tempStack.empty()) {
            cout << tempStack.top() << endl;
            tempStack.pop();
        }
    }

    
    void processRegistrationQueue() {
        cout << "Processing Registration Queue:" << endl;
        while (!registrationqueue.empty()) {
            cout << "Processed: " << registrationqueue.front() << endl;
            registrationqueue.pop();
        }
    }

    void undoLastRegistration() {
        if (!registrationhis.empty()) {
            cout << "Undoing last registration: " << registrationhis.top() << endl;
            registrationhis.pop();
        } else {
            cout << "No registrations to undo." << endl;
        }
    }
    
    void markVoterTurnReady() {
        int  id;
        cout << "Enter voter ID to mark as ready: ";
        cin >> id;

        Node* voter = registrations.getVoterById(id);
        if (voter != nullptr && !voter->isCandidate) {
            voter->isReady = true;
            cout << "Voter " << id << " is now marked as ready for their turn." << endl;
        } else {
            cout << "Voter ID not found or the ID belongs to a candidate." << endl;
        }
    }
};

void DisplayHelp() {
    cout << "\n=== Voting System Help ===\n";
    cout << "This voting system allows you to create, view, and vote on proposals.\n";
    cout << "Here are the available commands:\n\n";

    cout << "1. create <proposal_name> - Create a new proposal with the specified name.\n";
    cout << "   Example: create 'Increase Budget'\n\n";

    cout << "2. vote <proposal_id> <yes/no> - Vote 'yes' or 'no' on a specific proposal.\n";
    cout << "   Example: vote 1 yes\n\n";

    cout << "3. view <proposal_id> - View the details of a specific proposal.\n";
    cout << "   Example: view 1\n\n";

    cout << "4. results <proposal_id> - View the current voting results of a specific proposal.\n";
    cout << "   Example: results 1\n\n";

    cout << "5. list - List all proposals with their current status and IDs.\n\n";

    cout << "6. help - Display this help section.\n\n";

    cout << "7. exit - Exit the voting system.\n\n";

    cout << "=== End of Help ===\n";
}



void handleCommand(const string& command) {
    stringstream ss(command);
    string action;
    ss >> action;

    if (action == "create") {
        string proposal_name;
        getline(ss, proposal_name);
        if (proposal_name.empty()) {
            cout << "Error: Proposal name is missing. Example: create 'Increase Budget'\n";
        } else {
            cout << "Proposal '" << proposal_name << "' created successfully.\n";
        }
    } else if (action == "vote") {
        int proposal_id;
        string vote;
        ss >> proposal_id >> vote;
        if (vote != "yes" && vote != "no") {
            cout << "Error: Invalid vote. Use 'yes' or 'no'. Example: vote 1 yes\n";
        } else {
            cout << "Vote '" << vote << "' recorded for proposal ID " << proposal_id << ".\n";
        }
    } else if (action == "view") {
        int proposal_id;
        ss >> proposal_id;
        if (ss.fail()) {
            cout << "Error: Proposal ID is missing or invalid. Example: view 1\n";
        } else {
            cout << "Displaying details for proposal ID " << proposal_id << "...\n";
        }
    } else if (action == "results") {
        int proposal_id;
        ss >> proposal_id;
        if (ss.fail()) {
            cout << "Error: Proposal ID is missing or invalid. Example: results 1\n";
        } else {
            cout << "Displaying voting results for proposal ID " << proposal_id << "...\n";
        }
    } else if (action == "list") {
        cout << "Listing all proposals...\n";
    } else if (action == "help") {
        DisplayHelp();
    } else if (action == "exit") {
        cout << "Exiting the voting system. Goodbye!\n";
        exit(0);
    } else {
        cout << "Unknown command. Type 'help' to see the available commands.\n";
    }
}

void displayHelp(){
    string command;

    cout << "=== Welcome to the Voting System ===\n";
    cout << "Type 'help' to see the available commands.\n";

    while (true) {
        cout << "\nPlease enter a command: ";
        getline(cin, command);

        if (command.empty()) {
            cout << "No command entered. Type 'help' to see the available commands.\n";
        } else {
            handleCommand(command);
        }
    }
}


void welcome() {
    cout << "###############################################################################################\n";
    cout << "#                                                                                             #\n";
    cout << "#                                  Welcome to the Voting System                               #\n";
    cout << "#                                                                                             #\n";
    cout << "###############################################################################################\n\n\n\n";
    cout << "###############################################################################################\n";
    cout << "#                                     Think Twice , Vote Wise                                 #\n";
    cout << "###############################################################################################\n\n";
}

void displayMenu() {
    cout << "-------------------------------------------------------------------------------------------------\n";
    cout << "                                       Voting Options: \n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    cout << "1. Vote for an election \n";//sharad
    cout << "2. Check result of an election \n";//mrigank
    cout << "3. Check Voter eligiblity \n";//gaurav//done
    cout << "4. Arrange an election \n";//utkarsh//done
    cout << "5. Register candidate or voter \n";//gaurav//candidate and voter needs two different functions//done
    cout<<  "6. Help corner  \n";//sharad//done
    cout<<  "7. Learn about the fairness of this system \n";//utkarsh//done
    cout << "--------------------------------------------------------------------------------------------------\n";
}

void registration() {

    RegistrationSystem l; 
    int x;
do{  
    cout<<"                             ************* Welcome For Registration *************          "<<endl;
    cout<<"   Options To Choose   "<<endl;
    cout<<" 1.Candidate Registration "<<endl;
    cout<<" 2.Voter Registration "<<endl;
    cout<<" 3.Undo Last Registraion "<<endl;
    cout<<" 4.Display All Registration "<<endl;
    cout<<" 5.Display Registration History "<<endl;
    cout<<" 6.Process Registration Queue "<<endl;
    cout<<" 7.Turn Ready For Specific Voter "<<endl;
    cout<<"Select One Option From The Above Options : ";
    cout<<"Press 0 to revert to main menu "<<endl;

    cin>>x;
  
    switch (x){
        case 1:
        l.registerCandidate();
         cout<<endl;
        break ;
        case 2:
        l.registerVoter();
         cout<<endl;
        break;
        case 3:
        l.undoLastRegistration();
         cout<<endl;
        break;
        case 4:
        l.displayAllRegistrations();
         cout<<endl;
        break;
        case 5:
        l.displayRegistrationHistory();
         cout<<endl;
        break;
        case 6:
        l.processRegistrationQueue();
         cout<<endl;
        break;
        case 7:
        l.markVoterTurnReady();
        break;
        case 0:
        displayMenu();
        choiced();
        break;
        default:
        cout<<" Invalid Option !! Please Choose  Correct One "<<endl;
        cout<<endl;
        break;
    }
    }
    while(x>=0);
    cout<<"Press 0 to revert to main menu... OR 1 to exit "<<endl;
int n1;
cin>>n1;
if(n1==0){
displayMenu();
choiced();
}
else{
    exit(0);
     }
}



void arrangeElection() {

cout<<"Select the city in which you want to conduct election :"<<endl;
string electionCity;
cin>>electionCity;
int n= cities1.size();

if(n<1){
    cout<<"Not adequate registrations .. "<<endl;
    cout<<"Try again later !!!!! "<<endl;
    exit(1);
}
  for(const auto &city :cities1){
    cout<<city<<endl;
}
cout<<"your unique code for this election is "<<endl;
cout<<random_int<<endl;
string filename="electionList.txt";
ofstream file(filename,ios::app);
if(!file){
    cerr<<"error : could not write into file \n";
    return ;
}
file<<" "<<random_int<<"\n";
file.close();
cout<<"Use this code while voting for an election "<<endl;
//ab tree bananna hai 
Node *temp=head;
while(temp!=nullptr){
    if(temp->isCandidate){
        if(temp->city==electionCity){
         int id1=temp->id;
         cout<<id1;
         string name= temp->name;
           b1.root= b1.insert(b1.root,id1,name);
            string filename="final_candidates.txt";
            ofstream file(filename,ios::app);
            if(!file){
                cerr<<"error : could not open file "<<endl;
                return ;
            }
            file<<temp->id<<" "<<"\n";
        }
    }
    temp=temp->next;
}

//city wise voters ke lie 
Node *temp2=head;
while(temp2!=nullptr){
    if(!temp2->isCandidate){
        if(temp2->city==electionCity){
            int id2=temp2->id;
            string name=temp2->name;
           b2.root= b2.insert(b2.root,id2,name);
            string filename="final_voters.txt";
            ofstream file(filename,ios::app);
            if(!file){
                cerr<<"error : could not find file "<<endl;
                return ;
            }
            file<<temp2->id<<" "<<"\n";
        }
    }
    temp2=temp2->next;
}
cout<<"Press 0 to revert to main menu... OR 1 to exit "<<endl;
int n1;
cin>>n1;
if(n1==0){
displayMenu();
choiced();
}
else{
    exit(0);
     }

}

void voteForElection() {

    cout<<"Enter the unique code for this election "<<endl;
    int cod;
       cin>>cod;
       
    if(cod==random_int){
 cout<<"Welcome to voting process "<<endl;

cout<<"Enter the id of voter:...."<<endl;
string id;
cin>>id;
if(!alreadyVoted[stoi(id)]){
    alreadyVoted[stoi(id)]=true;
if(b2.search(b2.root,stoi(id))){
cout<<"Opening the voting terminal ... "<<endl;
cout<<" Below is the list of candidates that have registered in your city "<<endl;
b1.displayCandidates(b1.root);
}
else{
    cout<<"Sorry ... you can not vote !!!"<<endl;
    exit(0);
}
cout<<"Enter the candidate id you want to vote : "<<endl;
string canid;
cin>>canid;
node * root;
if(b1.search(b1.root,stoi(canid))){
    cout<<"Vote for this candidate ????"<<endl;
    string choice;
    cin>>choice;
    if(choice=="yes"||choice=="YES"){
        cout<<"Your vote has been counted ..."<<endl;
     //max-heap bna sakta hu final voting process ke lie
    //create an priority queue using max - heap and after each vote update the priority 
    //linked using canid
      result[stoi(canid)]++;
      if(result[stoi(canid)]>maxVotes){
        maxVotes=result[stoi(canid)];
        leadingCandidate=stoi(canid);
      }

    }
    else
    {
         cout<<" your vote could not be processed "<<endl;
         cout<<"Try again "<<endl;

    }

}
else{

    cout<<"Wrong candidate id !!! . Try again "<<endl;
}
    }

else{
cout<<"Wrong code !!! Please enter correct code "<<endl;

    exit(0);
     }


}
else{
    cout<<"Already Voted..."<<endl;
    exit(0);
}


cout<<"Press 0 to revert to main menu... OR 1 to exit "<<endl;
int n1;
cin>>n1;
if(n1==0){
displayMenu();
choiced();
}
else{
    exit(0);
     }

}


void heapify(vector<int>& arr, int n, int i){
    int largest = i;

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr){
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {

        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

void checkResult() {
    
    
    cout<<"Welcome to result checking section !!!! "<<endl;
    cout<<"Enter the code of election of which you want to check results "<<endl;
    float cod;
    cin>>cod;
    string name;
    if(cod==random_int){
    int winner_id= leadingCandidate;
    if(b1.search(b1.root,winner_id)){
        node *result=b1.search(b1.root,winner_id);
        name=result->name;
      
    }
    cout<<"Final winner is "<<name<< "with "<<result[leadingCandidate]<<" votes "<<endl;
    exit(0);    

    }
    else{
      cout<<"Sorry !! wrong code . Try again "<<endl;
      exit(0);

    }
    cout<<"Press 0 to revert to main menu... OR 1 to exit "<<endl;
int n1;
cin>>n1;
if(n1==0){
displayMenu();
choiced();
}
else{
    exit(0);
     }


}

void votingStatus() {
     cout<<"Enter city .."<<endl;
     string city;
     cin>>city;
    
     cout<<"Enter your birth year  ..."<<endl;
     int bday;
     cin>>bday;
     cout<<"checking status ...";
     int currYear=2024;
     if(currYear-bday>18){
      cout<<"HORRAH !!!! You are eligible for voting .."<<endl;
     }
      else cout<<"SORRY .. PLEASE VOTE FROM NEXT ELECTION "<<endl;
    
    cout<<"Press 0 to revert to main menu... OR 1 to exit "<<endl;
int n1;
cin>>n1;
if(n1==0){
displayMenu();
choiced();
}
else{
    exit(0);
     }


}

void helpSection() {
//help corner 
 string command;
    
    cout << "Welcome to the Voting System! Type 'help' for a list of commands.\n";
    
    while (true) {
        cout << "> ";
        cin >> command;
        
        if (command == "help") {
            displayHelp();
        }
        else if (command == "exit") {
            cout << "Exiting the voting system.\n";
            break;
        }
        else {
            cout << "Command not recognized. Type 'help' for a list of commands.\n";
        }
    }
    cout<<"Press 0 to revert to main menu... OR 1 to exit "<<endl;
int n1;
cin>>n1;
if(n1==0){
displayMenu();
choiced();
}
else{
    exit(0);
     }
    
}

void fairness() {
   
     cout << "=== Fairness in Voting Systems ===\n\n";

    cout << "1. **Prevent Double Voting**\n";
    cout << "   Each participant should only be able to vote once per proposal. Allowing\n";
    cout << "   multiple votes from the same person could unfairly skew the results,\n";
    cout << "   favoring one outcome over another. By tracking each voter's participation\n";
    cout << "   with unique identifiers, the system prevents any single user from casting\n";
    cout << "   more than one vote per proposal, thus maintaining integrity.\n\n";
    
    cout << "2. **Ensure Transparency**\n";
    cout << "   Fairness is also rooted in transparency, where participants can see the\n";
    cout << "   results and understand that the process was conducted honestly. A\n";
    cout << "   transparent system displays vote counts and allows participants to verify\n";
    cout << "   that their votes were recorded accurately. Transparency builds trust in\n";
    cout << "   the system, assuring voters that no hidden manipulations have occurred.\n\n";
    
    cout << "3. **Protect Against Bias**\n";
    cout << "   To achieve true fairness, a voting system must also be impartial. This\n";
    cout << "   means that it should not favor any particular candidate, proposal, or\n";
    cout << "   outcome. The system itself should operate neutrally, without introducing\n";
    cout << "   bias through vote counting or proposal handling processes.\n\n";
    
    cout << "=== Conclusion ===\n";
    cout << "In summary, a fair voting system is one that prevents double voting, maintains\n";
    cout << "transparency, protects against bias, and allows for audits. By adhering to\n";
    cout << "these principles, a voting system can ensure that every participant has an\n";
    cout << "equal and honest opportunity to make their voice heard, fostering trust and\n";
    cout << "confidence in the democratic process.\n";
    cout << "=== End of Fairness Explanation ===\n\n";
      

    cout<<"Press 0 to revert to main menu... OR 1 to exit "<<endl;
int n1;
cin>>n1;
if(n1==0){
displayMenu();
choiced();
}
else{
    exit(0);
     }
    
}

void choiced(){

    int choice;
    while (true) {
        cout << "Please enter the number of your choice (1-8) or 0 to exit: ";
        cin >> choice;
        if (choice == 0) {
            cout << "Exiting voting system. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1:
                voteForElection();
                
                break;
            case 2:
                checkResult();
                
                break;
            case 3:
                votingStatus();
               
                break;
            case 4:
                arrangeElection();
               
                break;
            case 5:
                registration();
              
                break;
           
                break;
            case 6:
                helpSection();
                
                break;
            case 7:
                fairness();
                
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

int main() {

    welcome();

    displayMenu();
    
    choiced();
    priority_queue<candidateVotes,vector<candidateVotes>,Compare> maxHeap; 
    for (int i = 1; i <= 10; i++) {
        alreadyVoted[i] = false;
    }

    return 0;
}