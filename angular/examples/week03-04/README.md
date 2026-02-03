# Week 03-04 Angular Sandbox

This workspace wraps the directives, forms, and DI examples into a runnable Angular application with a lightweight backend that echoes form submissions.

## Prerequisites
- Node.js 20.x LTS
- npm 10+

## Install Dependencies
```bash
cd examples/week03-04
npm install
```

## Run the Backend (Terminal 1)
```bash
npm run server
```
The server listens on `http://localhost:4000` and logs incoming form payloads.

## Run the Angular App (Terminal 2)
```bash
npm start
```
The Angular CLI proxies `/api` requests to the backend via `proxy.conf.json`. Open `http://localhost:4200` and submit the form to see the echoed response below the button and in the backend console.

## Project Structure
- `src/app/app.routes.ts` — routes root path to the form sandbox.
- `src/app/examples/` — `FormSandboxComponent` and `RegistrationFormComponent` demonstrating directives, reactive forms, and DI.
- `src/app/shared/` — directives (`HighlightDirective`, `IfViewportDirective`) and API service/token for backend calls.
- `server.js` — Express backend that prints and returns the submitted fields.

## Next Steps
- Replace the mock backend with your real API.
- Add persistence (e.g., save to a database) or validation rules on the server.
- Expand routing with additional weeks’ examples.
