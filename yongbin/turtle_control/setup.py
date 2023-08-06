from setuptools import setup

package_name = 'turtle_control'

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
    maintainer='yongbin',
    maintainer_email='yblee001223@naver.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'cricle = turtle_control.draw_circle:main',
            'eight = turtle_control.draw_eight:main',
        ],
    },
)
