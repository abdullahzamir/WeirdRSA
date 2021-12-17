

#include "RSA.h"
#include "RSA.cpp"

int main(){
    cpp_int p,q,phi,n;
    int e;
    string msg;
    cout << "RSA\n";
    vector<cpp_int> dec;
    cpp_int dec_push;
    bool cp,cq,ce;
    int choice;
     char ch='n';
     _re:
    cout << "Generate Public and Private key\n";
            cout << "Enter prime p: ";
            cin >> p;
             cp = primality_check(p);
            cout << "Enter prime q: ";
            cin >> q;
             cq = primality_check(q);
             
             try{
             if(!cp)
                throw(1);
             if(!cq)
                throw(1.1);
            
            
        }
        catch(int){
            cout << "\nincorrect prime number: "<< p << "\n Redirecting...\n";
        goto _re;
        }
        catch(double){
            cout << "\nincorrect prime number: " << q << "\n Redirecting...\n";
        goto _re;
        }
            phi = (p-1)*(q-1);
            _re_:
            cout << "Enter e such that e is co-prime of " << phi << " :";
            cin >> e;
             if(!e_check(e,phi)){
                cout << "wrong exponent value, redirecting..\n";
                 goto _re_;
                 }

            n = p*q;
            system("cls");
             msg_padding m(p,q,e);

        
    
           
    cout << "Your public key n: " << n << " e: " << e << endl;
    cout << "Your private key p: " << p << " q: " << q << endl;
    re:
    cout << "\n[-] MENU: \n";
    cout << "  1. Encrypt Data\n"
         << "  2. Decrypt Data\n"
         << "  3. Encrypt file\n"
         << "  4. Decrypt file\n"
         << "  5. Exit\n";
    cout << "Enter you choice: ";
    cin >> choice;
    if(choice==1){
        cout << "Enter your message: ";
        getline(cin>>ws,msg);
        m.convert_to_int(msg);
        m.encrypt();
        m.encrypted_text();
        goto re;
    }
    if(choice==2) {
        
        cout << "Enter your private key \n";
        cout << "Enter prime p: ";
            cin >> p;
        cout << "Enter prime q: ";
            cin >> q;
        _e:
        cout << "Enter e: ";
            cin >> e;
        if(!e_check(e,phi)){
                cout << "wrong exponent or prime value, redirecting\n";
            goto _e;
        }


        cout << "Enter encrypted data(enter 0 to stop): ";
        msg_padding m_dec(p,q,e);
        do{
            cin >> dec_push;
            if(dec_push!=0)
            dec.push_back(dec_push);
        }while(!(dec_push == 0));
        m_dec.decrypt(dec);
        cout << "\nDecrypted text: ";
        m_dec.convert_to_string();
        goto re;
    }
    if(choice==3){
        string line,file_name;
        Encrypt_Decrypt_file edf(p,q,e);
        cout << "Enter file name: ";
        cin >> file_name;
        edf.ifile.open(file_name+".txt");
        if(!edf.ifile.is_open())
            edf.ifile.open(file_name+".txt");
        int m, n, size;  
        m = edf.ifile.tellg(); // tells where the pointer is now 
        edf.ifile.seekg(0, ios::end); // moves pointer to end of file
        n = edf.ifile.tellg();
        size = n - m;
    if (size == 0)
        cout << "The file is Empty or doesnt exist\n Exiting..",exit(0);
    edf.ifile.seekg(0); // moving pointer back to start 
        getline(edf.ifile,line);
        cout << line;
        edf.convert_to_int(line);
        cout << endl;
        edf.encrypt();
        edf.encryptfile(file_name);
        goto re;
    }
    if(choice ==4){
    string line,file_name;
         cout << "Enter your private key \n";
        cout << "Enter prime p: ";
            cin >> p;
        cout << "Enter prime q: ";
            cin >> q;
        cout << "Enter e: ";
            cin >> e;
        if(!e_check(e,phi))
                cout << "wrong exponent or prime value, Exiting..",system("pause"), exit(0);
         cout << "Enter file name: ";
        cin >> file_name;
        Encrypt_Decrypt_file df(p,q,e);
        df.decryptfile(file_name);
        goto re;
    }
    if(choice == 5)
        exit(1);
  
  system("pause");
}
