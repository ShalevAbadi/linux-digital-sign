## Digital Signature
**Overview:**  
Once the user provides a file, the program would generate a hash key out of the file using the *Folding Method*.  
Then, the hash key would be encrypted using a private key, which was generated through the *RSA algorithm*.  
Finally, in order to verify the file's digital signature, the encrypted hash would be decrypted using public key, which was also generated through the *RSA algorithm*, and the decrypted hash would be compared with the original hash.  
If the two are equal, the digitial signature process is valid and complete.  

**Usage:**  

Compiling:  
`make build`  
  
Generating Public & Private Keys:  
`make generate_keys`  
  
Signing a file:  
`make sign INPUT="yourFile"`  
  
Validating the Digital Signature:  
`make validate_signature INPUT="yourFile"`  
  
Cleanup:  
`make clean`  