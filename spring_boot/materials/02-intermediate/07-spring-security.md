# Module 7: Spring Security

**Level:** Intermediate  
**Time:** ~90 minutes

---

## Learning Objectives

- Add Spring Security and understand default behavior (all endpoints protected)
- Configure permitAll / authenticated / hasRole
- Implement in-memory and user-details–based authentication
- Protect REST APIs with stateless JWT (conceptual) or session-based auth

---

## 7.1 Dependencies

**Maven:**

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-security</artifactId>
</dependency>
```

**Gradle:**

```groovy
implementation 'org.springframework.boot:spring-boot-starter-security'
```

Once added, **every request** is secured: default login form, default user, and all endpoints require authentication unless configured otherwise.

---

## 7.2 Default Behavior

- **All endpoints** require authentication.
- **Default user:** `user`; password is printed in the console at startup (e.g. “Using generated security password: …”).
- **Login form:** Browser requests get a form login; API clients get 401 Unauthorized.

For REST APIs you typically disable form login and configure stateless auth (e.g. JWT) or HTTP Basic.

---

## 7.3 Basic Configuration (SecurityFilterChain)

Define a `SecurityFilterChain` bean to customize access:

```java
package com.example.demo.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.web.SecurityFilterChain;

@Configuration
@EnableWebSecurity
public class SecurityConfig {

    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/api/public/**").permitAll()
                .requestMatchers("/api/admin/**").hasRole("ADMIN")
                .requestMatchers("/api/**").authenticated()
                .anyRequest().permitAll()
            )
            .httpBasic();  // or .formLogin() for browser
        return http.build();
    }
}
```

- **permitAll()** — no authentication required.
- **authenticated()** — any authenticated user.
- **hasRole("ADMIN")** — user must have authority `ROLE_ADMIN` (Spring adds "ROLE_" prefix when you use hasRole).
- **httpBasic()** — HTTP Basic Auth for APIs; **formLogin()** for browser-based login.

---

## 7.4 In-Memory User (for Development)

```java
package com.example.demo.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.crypto.factory.PasswordEncoderFactories;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.provisioning.InMemoryUserDetailsManager;
import org.springframework.security.web.SecurityFilterChain;

@Configuration
@EnableWebSecurity
public class SecurityConfig {

    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/api/public/**").permitAll()
                .requestMatchers("/api/admin/**").hasRole("ADMIN")
                .requestMatchers("/api/**").authenticated()
                .anyRequest().permitAll()
            )
            .httpBasic();
        return http.build();
    }

    @Bean
    public UserDetailsService userDetailsService(PasswordEncoder passwordEncoder) {
        var user = User.builder()
            .username("user")
            .password(passwordEncoder.encode("password"))
            .roles("USER")
            .build();
        var admin = User.builder()
            .username("admin")
            .password(passwordEncoder.encode("admin"))
            .roles("USER", "ADMIN")
            .build();
        return new InMemoryUserDetailsManager(user, admin);
    }

    @Bean
    public PasswordEncoder passwordEncoder() {
        return PasswordEncoderFactories.createDelegatingPasswordEncoder();
    }
}
```

- **PasswordEncoder** — never store plain passwords; use BCrypt (default in createDelegatingPasswordEncoder).
- **roles("USER")** — adds authority `ROLE_USER`.

---

## 7.5 Database-Backed UserDetailsService

Load users from your database:

```java
@Service
public class CustomUserDetailsService implements UserDetailsService {

    private final UserRepository userRepository;

    public CustomUserDetailsService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        UserEntity user = userRepository.findByUsername(username)
            .orElseThrow(() -> new UsernameNotFoundException("User not found: " + username));
        return org.springframework.security.core.userdetails.User.builder()
            .username(user.getUsername())
            .password(user.getPasswordHash())  // already encoded
            .roles(user.getRole().name())
            .build();
    }
}
```

Spring Security will use this bean automatically if it’s the only `UserDetailsService` in the context.

---

## 7.6 CORS (for Frontend Apps)

If a frontend on another origin calls your API, configure CORS:

```java
@Configuration
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/api/**")
            .allowedOrigins("http://localhost:3000")
            .allowedMethods("GET", "POST", "PUT", "DELETE", "OPTIONS")
            .allowedHeaders("*")
            .allowCredentials(true);
    }
}
```

For security-sensitive apps, restrict origins and methods instead of `*`.

---

## 7.7 JWT (Conceptual)

For stateless REST APIs, a common approach is JWT:

1. **POST /auth/login** — validate credentials, return a JWT.
2. **Client** sends `Authorization: Bearer <token>` on each request.
3. **Filter** validates the token and sets the security context.

Implementation requires:

- A library (e.g. `jjwt`) to create/parse JWTs.
- A filter that runs before `UsernamePasswordAuthenticationFilter`, validates the token, and sets `SecurityContextHolder`.

Detailed JWT implementation is often covered in an “Advanced Security” or “REST + JWT” lesson; here we focus on SecurityFilterChain, roles, and UserDetailsService.

---

## 7.8 Summary

- **Starter:** Add `spring-boot-starter-security`; by default everything is protected.
- **SecurityFilterChain:** Configure `permitAll`, `authenticated`, `hasRole`, and `httpBasic`/`formLogin`.
- **UserDetailsService:** In-memory or database-backed users; use **PasswordEncoder** for passwords.
- **CORS:** Configure in `WebMvcConfigurer` when a separate frontend calls the API.

---

## Exercises

1. Configure `/api/public/health` as permitAll and `/api/users` as authenticated; test with HTTP Basic.
2. Add two in-memory users (user/password and admin/admin) and restrict `/api/admin/**` to ADMIN.
3. (Optional) Implement a simple User entity and repository and load users from the DB in UserDetailsService.
