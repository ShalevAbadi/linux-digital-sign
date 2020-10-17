## Digital Signature
**Overview:**  
Once the user provides a file, the program would use a hash function on the file, which uses the *Folding Method*.  
The hash function would then be encrypted using a private key, which is generated through the *RSA algorithm*.  
Finally, in order to verify the file's digital signature, the encrypted hash would be decrypted using public key, which is also generated through the *RSA algorithm*, and the decrypted hash would be compared with the original hash.  
If the two are equal, the digitial signature process is valid and complete.  
  
The public key should go inside a file named rsa.public.  
The signature should go inside a file named signature.enc.  
Both files should be located inside the same directory.  
  
**Usage:**  

Compiling:  
`make build`  
    
Validating the Digital Signature:  
`make validate_signature INPUT="yourFile"`  
  
Generating your own Public & Private Keys:  
`make generate_keys`  
  
Signing a file:  
`make sign INPUT="yourFile"`  
  
Cleanup:  
`make clean`  
  
By:  
Shalev Abadi  
Omer Bresinski

