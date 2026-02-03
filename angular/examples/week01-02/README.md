# Week 01-02 Angular Sandbox

This workspace packages the component library examples from Weeks 1-2 into a runnable Angular application.

## Prerequisites
- Node.js 20.x LTS
- npm 10+

## Install Dependencies
```bash
cd examples/week01-02
npm install
```

## Run the Sandbox
```bash
npm start
```

The application serves on [http://localhost:4200](http://localhost:4200) by default. Use `npm start -- --port 4300` or edit `angular.json` to change the port.

## Project Structure
- `src/app/ui/` — standalone UI components (`ui-button`, `ui-card`, `ui-modal`, and `app-sandbox`).
- `src/app/app.routes.ts` — routes `/` to the sandbox showcase.
- `src/main.ts` — bootstraps the Angular application using standalone APIs.

Feel free to extend the sandbox with Storybook, additional components, or Story-driven exercises.
