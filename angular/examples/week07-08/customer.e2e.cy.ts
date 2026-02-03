// @ts-nocheck
describe('Customer CRUD', () => {
  beforeEach(() => {
    cy.intercept('GET', '/api/customers', { fixture: 'customers.json' }).as('loadCustomers');
    cy.visit('/customers');
    cy.wait('@loadCustomers');
  });

  it('creates a new customer', () => {
    cy.contains('New Customer').click();
    cy.get('input[formcontrolname="name"]').type('Grace Hopper');
    cy.get('input[formcontrolname="email"]').type('grace@example.com');
    cy.get('select[formcontrolname="status"]').select('active');

    cy.intercept('POST', '/api/customers', {
      id: '999',
      name: 'Grace Hopper',
      email: 'grace@example.com',
      status: 'active',
    }).as('createCustomer');

    cy.contains('Save').click();
    cy.wait('@createCustomer');
    cy.contains('Grace Hopper').should('exist');
  });
});
