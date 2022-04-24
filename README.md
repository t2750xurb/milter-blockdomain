milter-blockdomain 1.05   April 24th., 2022  

The milter-blockdomain is a simple milter written in C to maintain thousands of  
block domains in simple plain expression.  

- Separate configuration file and white/grey/black domain list files.
- Domain list file is auto-loaded when it is updated.  
  No restarting milter is required.
- Check FQDN of dns reverse lookup name, helo, envelope from and/or envelope recipient.  
  One domain entry in the domain list is applied to them.
- Domain entry is a simple plain expression.  
  No escape character of regular expression is required.  
  Domain is checked exact matching or domain boundary suffix matching
  as config settings.

It is a practical use that making use of both the milter-blockdomain and the milter-greylist.  
The milter-greylist works for unsolved IP address, malformed HELO/EHLO,
GeoIP, and/or S25R,  
widely applied rule by regular expression.  
It is good that the milter-blockdomain handle undesirable domain which is allowed  
by auto-whitelist of the milter-greylist.  
The milter-regex is also useful.

Equivalent block list expression
```
|--------------------+-----------------------------------------------------------|
| milter-blockdomain | exapmle.com                                               |
|--------------------+-----------------------------------------------------------|
| milter-greylist    | racl blacklist domain example.com                         |
|                    | racl blacklist helo /^(.+\.)?exapmle\.com$/               |
|                    | racl blacklist from /[.@]exapmle\.com>$/                  |
|--------------------+-----------------------------------------------------------|
| milter-regex       | connect /^(.+\.)?exapmle\.com$/ei // and envrcpt /^<.*>$/ |
|                    | helo    /^(.+\.)?exapmle\.com$/ei    and envrcpt /^<.*>$/ |
|                    | envfrom /[.@]exapmle\.com>$/i        and envrcpt /^<.*>$/ |
|--------------------+-----------------------------------------------------------|
```
