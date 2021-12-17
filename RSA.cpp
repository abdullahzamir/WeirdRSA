#include "RSA.h"

generating_key::generating_key(cpp_int p,cpp_int q,int e){
        this->p=p;
        this->q=q;
        this->e=e;
        phi = (p-1)*(q-1);
        n = p*q;
        d = calculate_d();
} 

 double generating_key::calculate_d(){
	int k=1;
 //while (((k*phi)+1)%e != 0) 
	while(fmod((k*(boost::lexical_cast<int>(phi))+1),e) != 0)   // to find k = such that e*d mod phi = 1 
	    k++;    
	
    d = boost::lexical_cast<double>(((k*phi)+1)/e);
    return d;
}

cpp_int gcd(cpp_int x,cpp_int y){
    	int j = 1;
	cpp_int gcd;
	while(j<=x&&j<=y){
		if(x%j==0&&y%j==0)
		gcd=j;
	j++;	
	}
	return gcd;	

}

bool e_check(int e,cpp_int phi){
	if(gcd( e,phi)==1)
		return true;
	else
	 	return false;
}

bool primality_check(cpp_int x){
         for(int i = 2;i<(x/2);i++)
	        if(x%i==0)
		        return false;

    return true;
}
encrypt_decrypt::encrypt_decrypt(cpp_int p=11,cpp_int q=13, int e=7):generating_key(p,q,e){}

void encrypt_decrypt::encrypt(){
    for(i = padded_m.begin();i!=padded_m.end();i++){
        push_c=(pow(*i,e)%n);
        c.push_back(push_c);
    }    
    cout << "Your encrypted data: ";
    for(i = c.begin();i!=c.end();i++){
        cout << *i << " ";
    }    
}

void encrypt_decrypt::encrypted_text(){
    cout << "\nText: "; 
    for(i=c.begin();i!=c.end();i++){
        en_text.push_back(char(*i));
        cout << (char(*i));
    }
}
void encrypt_decrypt::decrypt(vector<cpp_int> dec){
  // cout << "D: " << d;   
     for(i = dec.begin();i!=dec.end();i++){
       //  cout << *i << " ";
        push_decrypt=boost::multiprecision::pow(cpp_int(*i),d)%n;
        decrypted.push_back(push_decrypt);
    } 
    cout << "\ndecrypted data: ";
      for(i = decrypted.begin();i!=decrypted.end();i++){
        cout << (*i) << " ";
    } 
}
msg_padding::msg_padding(){}
msg_padding::msg_padding(cpp_int p,cpp_int q,int e):encrypt_decrypt(p,q,e){}

void msg_padding::convert_to_int(string s){
//getline(cin,s);
s.erase(remove(s.begin(),s.end(),' '),s.end());
// cout << s << endl;

// padding 
for(int i=0;i<s.length();i++){
    padded_m.push_back(int(s[i]-96));
    }

}

void msg_padding::convert_to_string(){
        for(boost_i = decrypted.begin();boost_i!=decrypted.end();boost_i++){
        cout << char(boost::lexical_cast<int>(*boost_i)+96);
    }
}   
Encrypt_Decrypt_file::Encrypt_Decrypt_file(cpp_int p,cpp_int q, int e):msg_padding(p,q,e){};

void Encrypt_Decrypt_file::encryptfile(string file_name){
    ofile.open(file_name+".enc");
    for(encrypt_decrypt::i=encrypt_decrypt::c.begin();encrypt_decrypt::i!=encrypt_decrypt::c.end();encrypt_decrypt::i++){
    ofile << *(encrypt_decrypt::i) << " ";
    }
    ofile.close();
}

void Encrypt_Decrypt_file::decryptfile(string file_name){
    ifile.open(file_name+".enc",ios::in);
    if(!ifile.is_open())
        cout << "\nno such file exists\n Exiting..",exit(0);
    ofile.open(file_name+"_decrypt.txt");
    string line;
    cpp_int n;
    while(ifile >> n){
        padded_m.push_back(n);
    }
    getline(ifile,line);
    //convert_to_int(line);
    decrypt(padded_m); 
    for(encrypt_decrypt::boost_i = encrypt_decrypt::decrypted.begin();encrypt_decrypt::boost_i!=encrypt_decrypt::decrypted.end();encrypt_decrypt::boost_i++){
        ofile << char(boost::lexical_cast<int>(*(encrypt_decrypt::boost_i))+96);

    }
}