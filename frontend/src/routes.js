import { createRouter, createWebHistory } from 'vue-router';
const routes = [
  {

    path: '/',
    name: 'home',
    component: () => import('./components/HomeView')
  },
  {

    path: '/about',
    name: 'about',
    component: () => import('./components/AboutView')
  },
  {

    path: '/login',
    name: 'login',
    component: () => import('./components/LoginView')
  },
  {
    path: '/services',
    name: 'services',
    component: () => import('./components/ServicesView')
  },
  
  {
    path: '/contact',
    name: 'contact',
    component: () => import('./components/ContactView')
  },
  {
    path: '/pricing',
    name: 'pricing',
    component: () => import('./components/PricingView')
  },
  {
    path: '/user',
    name: 'user',
    component: () => import('./components/UserView')
  }
];

const router = createRouter({
  history: createWebHistory(),
  routes
});

export default router;
