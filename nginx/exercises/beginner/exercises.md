# Beginner Level Exercises

## Exercise 1: Basic Installation and Setup

1. Install NGINX on your system
2. Verify the installation with `nginx -v`
3. Start NGINX service
4. Access the default NGINX page in your browser
5. Stop and restart NGINX
6. Test configuration with `nginx -t`

## Exercise 2: Basic Server Configuration

1. Create a directory `/var/www/mysite`
2. Create an `index.html` file in that directory
3. Create a server block configuration to serve files from `/var/www/mysite`
4. Set the server name to `mysite.local`
5. Test and reload the configuration
6. Access your site in the browser (may need to add to `/etc/hosts`)

## Exercise 3: Serving Static Files

1. Create a website with HTML, CSS, JavaScript, and images
2. Configure NGINX to serve all these file types
3. Set up caching for images (1 year)
4. Set up caching for CSS and JS files (30 days)
5. Test file serving and caching headers

## Exercise 4: Multiple Server Blocks

1. Create two different websites in separate directories
2. Configure two server blocks for different domains:
   - `site1.local`
   - `site2.local`
3. Test that each domain serves the correct content
4. Create a default server block that returns 444

## Exercise 5: Directory Listings

1. Create a directory `/var/www/downloads` with some files
2. Configure NGINX to enable directory listing for `/downloads`
3. Set directory listing to show file sizes in human-readable format
4. Test directory listing in browser
5. Disable directory listing for other locations

## Exercise 6: Error Pages

1. Create custom 404.html and 50x.html error pages
2. Configure NGINX to use these custom error pages
3. Test 404 error by accessing non-existent page
4. Test 50x error (you may need to simulate backend error)

## Exercise 7: File Permissions

1. Create a website directory
2. Set proper ownership (nginx user)
3. Set proper permissions (755 for directories, 644 for files)
4. Test that NGINX can serve the files
5. Try incorrect permissions and see what errors occur

## Exercise 8: Configuration File Organization

1. Create separate configuration files in `/etc/nginx/conf.d/`
2. Create one file for each website
3. Ensure all files are included in main `nginx.conf`
4. Test that all configurations work
5. Practice enabling/disabling sites

