
scp -i ~/.ssh/atravesar-new.pem appy.py ubuntu@demo.atravesar.ca:/home/ubuntu/hotels/
scp -i ~/.ssh/atravesar-new.pem requirements ubuntu@demo.atravesar.ca:/home/ubuntu/hotels/

scp -i ~/.ssh/atravesar-new.pem -r templates/* ubuntu@demo.atravesar.ca:/home/ubuntu/hotels/templates/
