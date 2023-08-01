from setuptools import setup

package_name = 'robotics_camp_sy'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='viet-incsl',
    maintainer_email='hoangvietdo.bk@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'feed_forward_circle_node = robotics_camp.feed_forward_circle:main',
            'feed_forward_8_shape_node = robotics_camp.feed_forward_8_shape:main',
            'feed_back_circle_node = robotics_camp.feed_back_circle:main',
            'feed_back_8_shape_node = robotics_camp.feed_back_8_shape:main',
        ],
    },
)
