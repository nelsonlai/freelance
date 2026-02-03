# Intermediate Level Exercises

## Exercise 1: SSL/TLS Configuration

1. Generate a self-signed SSL certificate
2. Configure NGINX to serve HTTPS on port 443
3. Set up HTTP to HTTPS redirect
4. Configure strong SSL settings (TLS 1.2+, strong ciphers)
5. Test SSL configuration with browser and command line tools

## Exercise 2: Let's Encrypt Setup

1. Install Certbot
2. Set up a basic HTTP server block
3. Obtain Let's Encrypt certificate using Certbot
4. Verify auto-renewal is configured
5. Test certificate renewal (dry run)

## Exercise 3: Reverse Proxy

1. Set up a simple backend application (Node.js, Python, etc.)
2. Configure NGINX as reverse proxy to backend
3. Set proper proxy headers (X-Real-IP, X-Forwarded-For, etc.)
4. Test proxying functionality
5. Configure WebSocket support

## Exercise 4: Load Balancing

1. Set up 2-3 backend servers (can be on same machine, different ports)
2. Create an upstream block with all backend servers
3. Configure round-robin load balancing
4. Test that requests are distributed across servers
5. Configure weighted load balancing
6. Test failover by stopping one backend server

## Exercise 5: URL Rewriting

1. Set up HTTP to HTTPS redirect
2. Configure www to non-www redirect (or vice versa)
3. Create clean URLs (remove .php extension)
4. Set up RESTful URL routing
5. Test all redirects and rewrites

## Exercise 6: Caching

1. Set up proxy cache zone
2. Configure caching for backend responses
3. Set different cache times for different status codes
4. Test cache hits and misses
5. Configure browser caching for static files
6. Monitor cache effectiveness

## Exercise 7: Virtual Hosting

1. Set up 3 different websites with different domains
2. Configure name-based virtual hosting
3. Set up subdomains (www, blog, api)
4. Configure wildcard subdomain handling
5. Test all domains and subdomains

## Exercise 8: Advanced Caching

1. Set up separate cache zones for different content types
2. Configure cache purging mechanism
3. Implement stale-while-revalidate
4. Set up cache warming script
5. Monitor cache hit ratio

